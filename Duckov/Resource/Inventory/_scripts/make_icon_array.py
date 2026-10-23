# 테스트용 아이템 아이콘 Texture2DArray(.dds) 만들기
#   - 아이템 40개 정도를 ITEM_TYPE별로 골라 128x128로 맞추고, 밉맵까지 넣은 DX10 배열 DDS로 저장
#   - 포맷: DXGI_FORMAT_R8G8B8A8_UNORM, 일반 알파(straight). 엔진의 SrcAlpha/InvSrcAlpha 블렌드에 그대로 맞음
#   - 투명 픽셀의 RGB를 주변 색으로 채우고(bleed) 밉맵은 premultiply 상태에서 줄여서, 테두리에 검은 띠가 안 생기게 함
# 사용: python make_icon_array.py   -> ../IconArray/icons_test_128.dds, icon_index.csv, icons_test_preview.png
import csv, os, struct
import numpy as np
from PIL import Image, ImageDraw, ImageFont, ImageFilter

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
OUT = os.path.join(ROOT, "IconArray")
SIZE = 128
os.makedirs(OUT, exist_ok=True)

ITEMS = [r for r in csv.DictReader(open(os.path.join(ROOT, "items.csv"), encoding="utf-8-sig")) if r["icon"]]
def tags(r): return r["tags"].split("|")

# (ITEM_TYPE, ARMOR_SLOT, 고르는 조건, 개수) - ITEM_TYPE / ARMOR_SLOT 이름은 Client_Defines.h 기준
PICKS = [
    ("GUN",      "", lambda r: "Gun" in tags(r) and "GunType_AR" in tags(r),               2),
    ("GUN",      "", lambda r: "Gun" in tags(r) and "GunType_PST" in tags(r),              1),
    ("GUN",      "", lambda r: "Gun" in tags(r) and "GunType_SMG" in tags(r),              1),
    ("GUN",      "", lambda r: "Gun" in tags(r) and "GunType_SHT" in tags(r),              1),
    ("GUN",      "", lambda r: "Gun" in tags(r) and "GunType_SNP" in tags(r),              1),
    ("MELEE",    "", lambda r: "MeleeWeapon" in tags(r),              2),
    ("BULLET",   "", lambda r: "Bullet" in tags(r),                   4),
    ("ARMOR",    "HEAD", lambda r: "Helmat" in tags(r),               3),
    ("ARMOR",    "BODY", lambda r: "Armor" in tags(r),                3),
    ("BACKPACK", "", lambda r: "Backpack" in tags(r),                 3),
    ("TOTEM",    "", lambda r: "Totem" in tags(r),                    2),
    ("ATTACH",   "", lambda r: "Scope" in tags(r),                    1),
    ("ATTACH",   "", lambda r: "Muzzle" in tags(r),                   1),
    ("ATTACH",   "", lambda r: "Magazine" in tags(r),                 1),
    ("MEDICAL",  "", lambda r: "Medic" in tags(r),                    4),
    ("FOOD",     "", lambda r: "Food" in tags(r),                     2),
    ("FOOD",     "", lambda r: "Drink" in tags(r),                    2),
    ("MISC",     "", lambda r: "Key" in tags(r),                      1),
    ("MISC",     "", lambda r: "Luxury" in tags(r),                   2),
    ("MISC",     "", lambda r: "Gem" in tags(r),                      1),
    ("MISC",     "", lambda r: "Electric" in tags(r),                 1),
    ("MISC",     "", lambda r: "Tool" in tags(r),                     1),
    ("MISC",     "", lambda r: "Explosive" in tags(r),                1),
    ("MISC",     "", lambda r: "Material" in tags(r),                 1),
]

def pick_items():
    chosen, used_icons = [], set()
    for itype, aslot, pred, n in PICKS:
        cands = [r for r in ITEMS if pred(r) and r["icon"] not in used_icons and r["name_ko"]
                 and r["quality"].isdigit() and 1 <= int(r["quality"]) <= 6]
        # 등급이 고르게 섞이도록 등급별로 하나씩 돌아가며 고름
        by_q = {}
        for r in cands: by_q.setdefault(int(r["quality"]), []).append(r)
        qs = sorted(by_q); k = 0
        while n > 0 and any(by_q.values()):
            q = qs[k % len(qs)]; k += 1
            if by_q[q]:
                r = by_q[q].pop(0); chosen.append((itype, aslot, r)); used_icons.add(r["icon"]); n -= 1
    return chosen

def fit(path):
    """비율 유지해서 SIZE x SIZE 안에 가운데 정렬 (투명 여백)"""
    src = Image.open(path).convert("RGBA")
    s = SIZE / max(src.size)
    w, h = max(1, round(src.width * s)), max(1, round(src.height * s))
    out = Image.new("RGBA", (SIZE, SIZE), (0, 0, 0, 0))
    out.paste(src.resize((w, h), Image.LANCZOS), ((SIZE - w) // 2, (SIZE - h) // 2))
    return np.asarray(out).astype(np.float32) / 255.0

def bleed(img):
    """알파 0인 픽셀의 RGB를 주변 불투명 색으로 채움 (바이리니어/밉맵에서 검은 테두리 방지)"""
    a = img[..., 3:4]
    rgb = img[..., :3] * a
    acc_rgb, acc_a = rgb.copy(), a.copy()
    for radius in (1, 2, 4, 8, 16, 32):
        pr = np.stack([np.asarray(Image.fromarray((rgb[..., c] * 255).astype(np.uint8)).filter(ImageFilter.BoxBlur(radius)), np.float32) / 255 for c in range(3)], -1)
        pa = np.asarray(Image.fromarray((a[..., 0] * 255).astype(np.uint8)).filter(ImageFilter.BoxBlur(radius)), np.float32)[..., None] / 255
        need = acc_a < 1e-3
        acc_rgb = np.where(need, pr, acc_rgb); acc_a = np.where(need, pa, acc_a)
    fill = np.where(acc_a > 1e-4, acc_rgb / np.maximum(acc_a, 1e-4), 0)
    out = img.copy()
    out[..., :3] = np.where(a > 0, img[..., :3], fill)
    return out

def mips(img):
    """premultiply → 2x2 평균 → unpremultiply"""
    levels = [img]
    cur = img
    while cur.shape[0] > 1:
        pm = cur.copy(); pm[..., :3] *= pm[..., 3:4]
        h, w = pm.shape[0] // 2, pm.shape[1] // 2
        pm = pm.reshape(h, 2, w, 2, 4).mean(axis=(1, 3))
        a = pm[..., 3:4]
        nxt = pm.copy(); nxt[..., :3] = np.where(a > 1e-4, pm[..., :3] / np.maximum(a, 1e-4), pm[..., :3])
        # 투명 영역 색은 위 레벨 bleed 결과를 평균한 값 유지
        rgb_avg = cur[..., :3].reshape(h, 2, w, 2, 3).mean(axis=(1, 3))
        nxt[..., :3] = np.where(a > 1e-4, nxt[..., :3], rgb_avg)
        levels.append(nxt); cur = nxt
    return levels

def write_dds_array(path, slices):
    """DX10 확장 헤더 DDS: Texture2DArray, R8G8B8A8_UNORM, 밉맵 포함"""
    n = len(slices); nmips = len(slices[0])
    DDSD = 0x1 | 0x2 | 0x4 | 0x8 | 0x1000 | 0x20000          # CAPS|HEIGHT|WIDTH|PITCH|PIXELFORMAT|MIPMAPCOUNT
    header = struct.pack("<4s7I44x", b"DDS ", 124, DDSD, SIZE, SIZE, SIZE * 4, 0, nmips)
    header += struct.pack("<2I4s5I", 32, 0x4, b"DX10", 0, 0, 0, 0, 0)   # DDS_PIXELFORMAT (FourCC = DX10)
    header += struct.pack("<5I", 0x1000 | 0x8 | 0x400000, 0, 0, 0, 0)    # caps: TEXTURE|COMPLEX|MIPMAP
    # DDS_HEADER_DXT10: format 28 = R8G8B8A8_UNORM, dimension 3 = TEXTURE2D, arraySize, miscFlags2 1 = 알파 straight
    header += struct.pack("<5I", 28, 3, 0, n, 1)
    with open(path, "wb") as f:
        f.write(header)
        for levels in slices:                                    # 슬라이스마다 [밉0, 밉1, ...] 순서
            for lv in levels:
                f.write((np.clip(lv, 0, 1) * 255 + 0.5).astype(np.uint8).tobytes())

def main():
    chosen = pick_items()
    slices, rows = [], []
    for i, (itype, aslot, r) in enumerate(chosen):
        img = bleed(fit(os.path.join(ROOT, "Sprites", "Items", r["icon"])))
        slices.append(mips(img))
        rows.append({"slice": i, "typeID": r["typeID"], "name_ko": r["name_ko"], "ITEM_TYPE": itype, "ARMOR_SLOT": aslot,
                     "quality": r["quality"], "stackable": int(int(r["maxStack"]) > 1), "maxStack": r["maxStack"],
                     "weight": r["weight"], "price": r["value"], "icon_png": r["icon"], "desc_ko": r["desc_ko"]})
    dds = os.path.join(OUT, f"icons_test_{SIZE}.dds")
    write_dds_array(dds, slices)
    with open(os.path.join(OUT, "icon_index.csv"), "w", newline="", encoding="utf-8-sig") as f:
        w = csv.DictWriter(f, list(rows[0].keys())); w.writeheader(); w.writerows(rows)

    # 확인용 시트: 슬라이스 번호 + 이름
    cols = 8; cell = SIZE + 8; lab = 34
    sheet = Image.new("RGBA", (cols * cell, ((len(rows) + cols - 1) // cols) * (cell + lab)), (52, 58, 66, 255))
    d = ImageDraw.Draw(sheet)
    try: fnt = ImageFont.truetype(r"C:\Windows\Fonts\malgun.ttf", 13)
    except OSError: fnt = ImageFont.load_default()
    for i, (lv, row) in enumerate(zip(slices, rows)):
        x, y = (i % cols) * cell, (i // cols) * (cell + lab)
        im = Image.fromarray((np.clip(lv[0], 0, 1) * 255 + 0.5).astype(np.uint8), "RGBA")
        sheet.alpha_composite(im, (x + 4, y + 4))
        d.text((x + 4, y + SIZE + 6), f"[{i}] {row['ITEM_TYPE']}{'/' + row['ARMOR_SLOT'] if row['ARMOR_SLOT'] else ''} q{row['quality']}", font=fnt, fill=(255, 220, 150))
        d.text((x + 4, y + SIZE + 22), row["name_ko"][:12], font=fnt, fill=(255, 255, 255))
    sheet.save(os.path.join(OUT, "icons_test_preview.png"))
    print(f"{dds}: {len(slices)} slices, {len(slices[0])} mips, {os.path.getsize(dds)/1024/1024:.2f} MB")

if __name__ == "__main__":
    main()
