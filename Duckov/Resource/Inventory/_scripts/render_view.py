# 덤프한 UI 계층(Layout/*.json)으로 유니티 UI 레이아웃을 다시 계산해서 인벤토리 창을 그린다.
#   - RectTransform 앵커/피벗, Horizontal/Vertical/Grid LayoutGroup, LayoutElement, ContentSizeFitter 재현
#   - Image(Simple/Sliced/Filled), ProceduralImage(둥근 사각형), TranslucentImage(블러 배경 근사), TMP 텍스트, TrueShadow(근사)
#   - 게임 실행 중에 채워지는 칸(인벤토리/장비 슬롯/퀵슬롯)은 프리팹을 복제해 예시 아이템으로 채움
# 사용: python render_view.py            -> preview_inventory_tab.png, preview_inventory_loot.png
import json, csv, os, re, math, copy, sys
from PIL import Image, ImageDraw, ImageFilter, ImageFont, ImageChops
from fontTools.ttLib import TTFont

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
DUCKOV = os.path.abspath(os.path.join(ROOT, "..", ".."))
LOC = r"D:\STEAM\steamapps\common\Escape from Duckov\Duckov_Data\StreamingAssets\Localization\Korean.csv"
CW, CH = 2560, 1440          # CanvasScaler 기준 해상도
S = 1.0                      # 출력 배율

# ---------------- 데이터 ----------------
def load_json(name): return json.load(open(os.path.join(ROOT, "Layout", name), encoding="utf-8"))
KO = {}
with open(LOC, encoding="utf-8-sig", newline="") as f:
    for row in csv.reader(f):
        if len(row) >= 2: KO[row[0]] = re.sub(r"\\(.)", r"\1", row[1])
ITEMS = [r for r in csv.DictReader(open(os.path.join(ROOT, "items.csv"), encoding="utf-8-sig")) if r["icon"]]
QCOL = {}
for r in csv.DictReader(open(os.path.join(ROOT, "quality_colors.csv"), encoding="utf-8-sig")):
    if r["quality"].isdigit(): QCOL[int(r["quality"])] = tuple(int(r["hex"][i:i+2], 16) for i in (1, 3, 5))
SPR = {}
for r in csv.DictReader(open(os.path.join(ROOT, "Sprites", "ui_sprites_9slice.csv"), encoding="utf-8-sig")):
    SPR.setdefault(r["name"], r)
_img_cache = {}
def sprite_img(path):
    if path not in _img_cache: _img_cache[path] = Image.open(path).convert("RGBA")
    return _img_cache[path]

# 폰트: ResourceHanRoundedCN 에는 한글이 없어서 한글은 Jua(게임 폰트 폴더에 있음), 그 외는 맑은 고딕으로 대체
F_MAIN = os.path.join(ROOT, "Font", "ResourceHanRoundedCN-Medium.ttf")
F_KO = os.path.join(DUCKOV, "Resource_100", "Font", "Jua-Regular.ttf")
F_FB = r"C:\Windows\Fonts\malgun.ttf"
CMAPS = {p: set(TTFont(p, fontNumber=0).getBestCmap().keys()) for p in (F_MAIN, F_KO)}
ASC, DESC = 1.160, 0.288     # ResourceHan hhea (TMP 줄 높이 = 1.448 * size)
_font_cache = {}
def font(path, size):
    k = (path, int(round(size * 4)))
    if k not in _font_cache: _font_cache[k] = ImageFont.truetype(path, max(1, k[1] / 4))
    return _font_cache[k]
def font_for(ch):
    o = ord(ch)
    if o in CMAPS[F_MAIN]: return F_MAIN
    if o in CMAPS[F_KO]: return F_KO
    return F_FB
def runs(text):
    out = []
    for ch in text:
        p = font_for(ch)
        if out and out[-1][0] == p: out[-1][1] += ch
        else: out.append([p, ch])
    return out
def text_width(text, size):
    return sum(font(p, size).getlength(t) for p, t in runs(text))

# ---------------- 노드 ----------------
class N:
    def __init__(s, d, parent=None):
        s.name = d["name"]; s.active = d.get("active", True); s.parent = parent
        r = d.get("rect") or {"anchorMin": [0, 0], "anchorMax": [1, 1], "pos": [0, 0], "size": [0, 0], "pivot": [.5, .5]}
        s.amin = list(r["anchorMin"]); s.amax = list(r["anchorMax"]); s.pos = list(r["pos"])
        s.sd = list(r["size"]); s.pv = list(r["pivot"]); s.scale = (r.get("scale") or [1, 1, 1])[0]
        s.comps = d.get("components", [])
        s.children = [N(c, s) for c in d.get("children", []) if "note" not in c]
        s.size = [0.0, 0.0]; s.lo = [0.0, 0.0]     # 부모 기준 좌하단(y-up)
        s.driven = [False, False]; s.inp = [(0, 0, 0), (0, 0, 0)]
    def c(s, t):
        for x in s.comps:
            if x["type"] == t: return x
    def find(s, path):
        n = s
        for part in path.split("/"):
            n = next((ch for ch in n.children if ch.name == part), None)
            if n is None: raise KeyError(path)
        return n
    def walk(s):
        yield s
        for ch in s.children: yield from ch.walk()
    def clone(s, parent=None):
        p = s.parent; s.parent = None
        c = copy.deepcopy(s); s.parent = p; c.parent = parent
        return c
def acts(n): return [c for c in n.children if c.active]
def lay_kids(n):
    out = []
    for c in acts(n):
        le = c.c("LayoutElement")
        if le and le.get("m_Enabled", 1) and le.get("m_IgnoreLayout"): continue
        out.append(c)
    return out
def group(n):
    for t in ("HorizontalLayoutGroup", "VerticalLayoutGroup", "GridLayoutGroup"):
        g = n.c(t)
        if g and g.get("m_Enabled", 1): return t, g
    return None, None

# ---------------- 텍스트 ----------------
def strip_tags(t): return re.sub(r"<[^>]+>", "", t or "")
def tmp_text(n):
    t = n.c("TextMeshProUGUI")
    return t, strip_tags(t.get("m_text", "")).rstrip("\n")
def wrap_lines(text, size, width, wrap):
    lines = []
    for para in text.split("\n"):
        if not wrap or width <= 0: lines.append(para); continue
        cur = ""
        for ch in para:
            if text_width(cur + ch, size) > width and cur:
                # 단어 단위(공백)로 끊기, 없으면 글자 단위
                if " " in cur and ch != " ":
                    i = cur.rfind(" "); lines.append(cur[:i]); cur = cur[i+1:] + ch
                else: lines.append(cur.rstrip()); cur = ch.lstrip()
            else: cur += ch
        lines.append(cur)
    return lines
def tmp_pref(n, axis, width=None):
    t, text = tmp_text(n)
    size = t["m_fontSizeMax"] if t.get("m_enableAutoSizing") else t["m_fontSize"]
    m = t.get("m_margin") or {"x": 0, "y": 0, "z": 0, "w": 0}
    if not text: return 0
    if axis == 0:
        return max(text_width(l, size) for l in text.split("\n")) + m["x"] + m["z"] + 0.0
    w = (width if width is not None else 1e9) - m["x"] - m["z"]
    lines = wrap_lines(text, size, w, t.get("m_enableWordWrapping", 1))
    lh = (ASC + DESC) * size
    return lh + (len(lines) - 1) * (lh + t.get("m_lineSpacing", 0) * size * 0.01) + m["y"] + m["w"]

# ---------------- 레이아웃 입력 (min, pref, flex) ----------------
def natural(c, axis, parent_size):
    """레이아웃 그룹이 크기를 제어하지 않을 때 자식의 현재 크기"""
    csf = c.c("ContentSizeFitter")
    if csf and csf.get("m_Enabled", 1):
        fit = csf["m_HorizontalFit" if axis == 0 else "m_VerticalFit"]
        if fit: return c.inp[axis][0 if fit == 1 else 1]
    return c.sd[axis] + (c.amax[axis] - c.amin[axis]) * parent_size if c.amax[axis] != c.amin[axis] else c.sd[axis]
def child_sizes(c, axis, control, expand, psize):
    if not control: v = natural(c, axis, psize); mn, pf, fl = v, v, 0
    else: mn, pf, fl = c.inp[axis]
    if expand: fl = max(fl, 1)
    return mn, pf, fl
def pad(g, axis):
    p = g["m_Padding"]
    return (p["m_Left"] + p["m_Right"]) if axis == 0 else (p["m_Top"] + p["m_Bottom"])
def hv_calc(n, g, axis, vertical):
    control = g["m_ChildControlWidth" if axis == 0 else "m_ChildControlHeight"]
    expand = g["m_ChildForceExpandWidth" if axis == 0 else "m_ChildForceExpandHeight"]
    sp = g["m_Spacing"]; P = pad(g, axis)
    tmin = tpref = P; tflex = 0
    other = vertical != (axis == 1)
    kids = lay_kids(n)
    for c in kids:
        mn, pf, fl = child_sizes(c, axis, control, expand, n.size[axis])
        if other: tmin = max(mn + P, tmin); tpref = max(pf + P, tpref); tflex = max(fl, tflex)
        else: tmin += mn + sp; tpref += pf + sp; tflex += fl
    if not other and kids: tmin -= sp; tpref -= sp
    return tmin, max(tmin, tpref), tflex
def grid_counts(n, g, count):
    cons, k = g["m_Constraint"], g["m_ConstraintCount"]
    cx, sx = g["m_CellSize"]["x"], g["m_Spacing"]["x"]
    if cons == 1: return k, max(1, math.ceil(count / k - 0.001))
    if cons == 2: return max(1, math.ceil(count / k - 0.001)), k
    w = n.size[0]
    cols = max(1, int((w - pad(g, 0) + sx + 0.001) // (cx + sx)))
    return cols, max(1, math.ceil(count / cols))
def grid_calc(n, g, axis):
    cnt = len(lay_kids(n)); cell = g["m_CellSize"]; sp = g["m_Spacing"]
    if axis == 0:
        cons, k = g["m_Constraint"], g["m_ConstraintCount"]
        if cons == 1: mc = pc = k
        elif cons == 2: mc = pc = max(1, math.ceil(cnt / k - 0.001))
        else: mc, pc = 1, max(1, math.ceil(math.sqrt(cnt)))
        return pad(g, 0) + (cell["x"] + sp["x"]) * mc - sp["x"], pad(g, 0) + (cell["x"] + sp["x"]) * pc - sp["x"], -1
    cols, rows = grid_counts(n, g, cnt)
    v = pad(g, 1) + (cell["y"] + sp["y"]) * rows - sp["y"]
    return v, v, -1
def image_pref(n, axis):
    for t in ("Image", "ProceduralImage", "TranslucentImage"):
        im = n.c(t)
        if not im or not im.get("m_Enabled", 1): continue
        sp = (im.get("m_Sprite") or "").split(":", 1)[-1]
        r = SPR.get(sp)
        if not r: return 0
        k = 100.0 / float(r["ppu"]) / im.get("m_PixelsPerUnitMultiplier", 1)
        if im.get("m_Type") in (1, 2):
            return (float(r["border_L"]) + float(r["border_R"])) * k if axis == 0 else (float(r["border_B"]) + float(r["border_T"])) * k
        return (float(r["w"]) if axis == 0 else float(r["h"])) * k
    return None
def calc_inputs(n, axis):
    for c in acts(n): calc_inputs(c, axis)
    cand = []
    t, g = group(n)
    if t == "GridLayoutGroup": cand.append(grid_calc(n, g, axis))
    elif t: cand.append(hv_calc(n, g, axis, t == "VerticalLayoutGroup"))
    if n.c("TextMeshProUGUI") and n.c("TextMeshProUGUI").get("m_Enabled", 1):
        v = tmp_pref(n, axis, n.size[0]); cand.append((0, v, -1))
    ip = image_pref(n, axis)
    if ip is not None: cand.append((0, ip, -1))
    mn = max([c[0] for c in cand], default=0); pf = max([c[1] for c in cand], default=0)
    fl = max([c[2] for c in cand], default=0); fl = max(fl, 0)
    svm = n.c("ScrollViewMaxHeight")
    if svm and axis == 1:      # 내용 높이만큼 늘어나다 maxHeight에서 멈춤 (스크롤)
        try: content = n.find("Viewport/Content"); ch = content.inp[1][1]
        except KeyError: ch = 0
        pf = min(ch, svm.get("maxHeight", 1e9))
    le = n.c("LayoutElement")
    if le and le.get("m_Enabled", 1) and not le.get("m_IgnoreLayout"):
        k = ("m_MinWidth", "m_PreferredWidth", "m_FlexibleWidth") if axis == 0 else ("m_MinHeight", "m_PreferredHeight", "m_FlexibleHeight")
        if le[k[0]] >= 0: mn = le[k[0]]
        if le[k[1]] >= 0: pf = le[k[1]]
        if le[k[2]] >= 0: fl = le[k[2]]
    n.inp[axis] = (mn, max(mn, pf), fl)

# ---------------- 레이아웃 배치 ----------------
def set_child(c, axis, pos_from_start, size, parent_size):
    """LayoutGroup이 자식 배치: 좌/상단 기준 offset -> 부모 좌하단 기준 lo"""
    if size is not None: c.size[axis] = size
    c.lo[axis] = pos_from_start if axis == 0 else parent_size - pos_from_start - c.size[axis]
    c.driven[axis] = True
def start_offset(n, g, axis, req):
    avail = n.size[axis]; surplus = avail - (req + pad(g, axis))
    al = g["m_ChildAlignment"]; a = (al % 3) * 0.5 if axis == 0 else (al // 3) * 0.5
    return (g["m_Padding"]["m_Left"] if axis == 0 else g["m_Padding"]["m_Top"]) + surplus * a
def hv_set(n, g, axis, vertical):
    control = g["m_ChildControlWidth" if axis == 0 else "m_ChildControlHeight"]
    expand = g["m_ChildForceExpandWidth" if axis == 0 else "m_ChildForceExpandHeight"]
    sp = g["m_Spacing"]; size = n.size[axis]
    al = g["m_ChildAlignment"]; align = (al % 3) * 0.5 if axis == 0 else (al // 3) * 0.5
    other = vertical != (axis == 1); kids = lay_kids(n)
    if other:
        inner = size - pad(g, axis)
        for c in kids:
            mn, pf, fl = child_sizes(c, axis, control, expand, size)
            req = max(mn, min(inner, size if fl > 0 else pf))
            so = start_offset(n, g, axis, req)
            if control: set_child(c, axis, so, req, size)
            else: c.size[axis] = natural(c, axis, size); set_child(c, axis, so + (req - c.size[axis]) * align, None, size)
    else:
        tmin, tpref, tflex = n.inp_group[axis]
        pos = g["m_Padding"]["m_Left"] if axis == 0 else g["m_Padding"]["m_Top"]
        mult = 0; surplus = size - tpref
        if surplus > 0:
            if tflex == 0: pos = start_offset(n, g, axis, tpref - pad(g, axis))
            elif tflex > 0: mult = surplus / tflex
        lerp = 0
        if tmin != tpref: lerp = max(0, min(1, (size - tmin) / (tpref - tmin)))
        for c in kids:
            mn, pf, fl = child_sizes(c, axis, control, expand, size)
            cs = mn + (pf - mn) * lerp + fl * mult
            if control: set_child(c, axis, pos, cs, size)
            else: c.size[axis] = natural(c, axis, size); set_child(c, axis, pos + (cs - c.size[axis]) * align, None, size)
            pos += cs + sp
def grid_set(n, g, axis):
    kids = lay_kids(n); cell = g["m_CellSize"]; sp = g["m_Spacing"]
    for c in kids: c.size[axis] = cell["x" if axis == 0 else "y"]; c.driven[axis] = True
    if axis == 0: return
    cnt = len(kids)
    if not cnt: return
    cols, rows = grid_counts(n, g, cnt)
    if g["m_StartAxis"] == 0: per = cols; ax = max(1, min(cols, cnt)); ay = max(1, min(rows, math.ceil(cnt / per)))
    else: per = rows; ay = max(1, min(rows, cnt)); ax = max(1, min(cols, math.ceil(cnt / per)))
    req = (ax * cell["x"] + (ax - 1) * sp["x"], ay * cell["y"] + (ay - 1) * sp["y"])
    so = (start_offset(n, g, 0, req[0]), start_offset(n, g, 1, req[1]))
    sc = g["m_StartCorner"]
    for i, c in enumerate(kids):
        if g["m_StartAxis"] == 0: px, py = i % per, i // per
        else: px, py = i // per, i % per
        if sc % 2 == 1: px = ax - 1 - px
        if sc // 2 == 1: py = ay - 1 - py
        set_child(c, 0, so[0] + (cell["x"] + sp["x"]) * px, None, n.size[0])
        set_child(c, 1, so[1] + (cell["y"] + sp["y"]) * py, None, n.size[1])
def set_layout(n, axis, psize):
    if not n.driven[axis]:
        csf = n.c("ContentSizeFitter"); fit = 0
        if csf and csf.get("m_Enabled", 1): fit = csf["m_HorizontalFit" if axis == 0 else "m_VerticalFit"]
        if fit: n.size[axis] = n.inp[axis][0 if fit == 1 else 1]
        else: n.size[axis] = (n.amax[axis] - n.amin[axis]) * psize + n.sd[axis]
        ref = (n.amin[axis] + (n.amax[axis] - n.amin[axis]) * n.pv[axis]) * psize
        n.lo[axis] = ref + n.pos[axis] - n.size[axis] * n.pv[axis]
    t, g = group(n)
    if t == "GridLayoutGroup": grid_set(n, g, axis)
    elif t: hv_set(n, g, axis, t == "VerticalLayoutGroup")
    for c in acts(n):
        if c.driven[axis] and t is None: c.driven[axis] = False
        set_layout(c, axis, n.size[axis])
def store_group_inputs(n, axis):
    for c in acts(n): store_group_inputs(c, axis)
    t, g = group(n)
    if not hasattr(n, "inp_group"): n.inp_group = [None, None]
    if t in ("HorizontalLayoutGroup", "VerticalLayoutGroup"): n.inp_group[axis] = hv_calc(n, g, axis, t == "VerticalLayoutGroup")
def reset_driven(n):
    for x in n.walk(): x.driven = [False, False]
def do_layout(root):
    for it in range(2):      # 텍스트 줄바꿈/스크롤 높이가 폭에 의존해서 두 번 돈다
        reset_driven(root)
        calc_inputs(root, 0); store_group_inputs(root, 0); set_layout(root, 0, CW)
        calc_inputs(root, 1); store_group_inputs(root, 1); set_layout(root, 1, CH)

# ---------------- 그리기 ----------------
def col(c, a_mul=1.0):
    if not isinstance(c, dict): return (255, 255, 255, 255)
    return tuple(int(round(max(0, min(1, v)) * 255)) for v in (c["r"], c["g"], c["b"])) + (int(round(max(0, min(1, c["a"] * a_mul)) * 255)),)
def tint(im, c):
    if c == (255, 255, 255, 255): return im
    r, g, b, a = im.split()
    r = r.point(lambda v: v * c[0] // 255); g = g.point(lambda v: v * c[1] // 255)
    b = b.point(lambda v: v * c[2] // 255); a = a.point(lambda v: v * c[3] // 255)
    return Image.merge("RGBA", (r, g, b, a))
def nine(src, w, h, b, fill_center=True):
    """b = (L,B,R,T) 출력 픽셀 단위 테두리, src 테두리는 원본 픽셀"""
    L, B, R, T, sl, sb, sr, st = b
    out = Image.new("RGBA", (w, h), (0, 0, 0, 0)); W, H = src.size
    # 테두리가 영역보다 크면 비율로 줄임 (유니티와 동일)
    if L + R > w and L + R > 0: k = w / (L + R); L, R = L * k, R * k
    if B + T > h and B + T > 0: k = h / (B + T); B, T = B * k, T * k
    xs = [0, round(L), w - round(R), w]; ys = [0, round(T), h - round(B), h]
    sx = [0, sl, W - sr, W]; sy = [0, st, H - sb, H]
    for i in range(3):
        for j in range(3):
            if i == 1 and j == 1 and not fill_center: continue
            dw, dh = xs[i+1] - xs[i], ys[j+1] - ys[j]
            if dw <= 0 or dh <= 0 or sx[i+1] <= sx[i] or sy[j+1] <= sy[j]: continue
            out.paste(src.crop((sx[i], sy[j], sx[i+1], sy[j+1])).resize((dw, dh), Image.BILINEAR), (xs[i], ys[j]))
    return out
def rrect_img(w, h, radius, fill, outline_w=0, corners=None):
    ss = 3
    im = Image.new("RGBA", (max(1, w * ss), max(1, h * ss)), (0, 0, 0, 0))
    d = ImageDraw.Draw(im); r = max(0, min(radius, w / 2, h / 2)) * ss
    box = [0, 0, w * ss - 1, h * ss - 1]
    if outline_w > 0: d.rounded_rectangle(box, r, outline=fill, width=max(1, int(outline_w * ss)), corners=corners)
    else: d.rounded_rectangle(box, r, fill=fill, corners=corners)
    return im.resize((max(1, w), max(1, h)), Image.LANCZOS)
def fill_crop(im, comp):
    if comp.get("m_Type") != 3: return im
    a = comp.get("m_FillAmount", 1); m = comp.get("m_FillMethod", 0); o = comp.get("m_FillOrigin", 0)
    w, h = im.size; mask = Image.new("L", im.size, 0); d = ImageDraw.Draw(mask)
    if m == 0:
        x = w * a; d.rectangle([0, 0, x, h] if o == 0 else [w - x, 0, w, h], fill=255)
    elif m == 1:
        y = h * a; d.rectangle([0, h - y, w, h] if o == 0 else [0, 0, w, y], fill=255)
    else: d.rectangle([0, 0, w, h], fill=255)
    out = im.copy(); out.putalpha(ImageChops.multiply(im.split()[3], mask)); return out
def radius_of(n, w, h):
    if n.c("RoundModifier"): return min(w, h) / 2, None
    u = n.c("UniformModifier")
    if u: return u.get("radius", 0), None
    f = n.c("FreeModifier")
    if f and isinstance(f.get("radius"), dict):
        r = f["radius"]; vals = [r["x"], r["y"], r["z"], r["w"]]
        return max(vals), tuple(v > 0 for v in vals)
    o = n.c("OnlyOneEdgeModifier")
    if o: return o.get("radius", 0), None
    return 0, None

BG = None; BG_BLUR = None
def composite(dst, im, x, y):
    x, y = int(round(x)), int(round(y))
    sx0, sy0 = max(0, -x), max(0, -y)
    if sx0 >= im.width or sy0 >= im.height: return
    if sx0 or sy0: im = im.crop((sx0, sy0, im.width, im.height)); x += sx0; y += sy0
    if x >= dst.width or y >= dst.height: return
    if x + im.width > dst.width or y + im.height > dst.height:
        im = im.crop((0, 0, min(im.width, dst.width - x), min(im.height, dst.height - y)))
    dst.alpha_composite(im, (x, y))
def shadow_of(graphic, ts, k):
    """TrueShadow 근사: 그래픽 알파를 퍼뜨리고 흐린 뒤 색을 입힌다"""
    size = ts.get("size", 0) * k; c = col(ts.get("color"))
    pad_ = int(size * 2 + abs(ts.get("offsetDistance", 0)) * k + 4)
    a = Image.new("L", (graphic.width + pad_ * 2, graphic.height + pad_ * 2), 0)
    a.paste(graphic.split()[3], (pad_, pad_))
    sp = ts.get("spread", 0)
    if sp > 0: a = a.filter(ImageFilter.MaxFilter(3))
    if size > 0: a = a.filter(ImageFilter.GaussianBlur(size / 2))
    a = a.point(lambda v: v * c[3] // 255)
    out = Image.new("RGBA", a.size, c[:3] + (0,)); out.putalpha(a)
    ang = math.radians(ts.get("offsetAngle", 90)); d = ts.get("offsetDistance", 0) * k
    return out, -pad_ + math.cos(ang) * d, -pad_ + math.sin(ang) * d
def inset_glow(graphic, ts, k):
    c = col(ts.get("color")); size = ts.get("size", 0) * k
    a = graphic.split()[3]
    inv = ImageChops.invert(a).filter(ImageFilter.GaussianBlur(max(1, size / 2)))
    g = ImageChops.multiply(a, inv).point(lambda v: min(255, v * 2) * c[3] // 255)
    out = Image.new("RGBA", graphic.size, c[:3] + (0,)); out.putalpha(g); return out

def draw_text(dst, n, x, y, w, h, k):
    t, text = tmp_text(n)
    if not text or not t.get("m_Enabled", 1): return
    m = t.get("m_margin") or {"x": 0, "y": 0, "z": 0, "w": 0}
    x += m["x"] * k; y += m["y"] * k; w -= (m["x"] + m["z"]) * k; h -= (m["y"] + m["w"]) * k
    wrap = t.get("m_enableWordWrapping", 1)
    size = t["m_fontSize"]
    if t.get("m_enableAutoSizing"):
        size = t["m_fontSizeMax"]
        while size > t["m_fontSizeMin"]:
            lines = wrap_lines(text, size, w / k, wrap)
            tw = max(text_width(l, size) for l in lines); th = len(lines) * (ASC + DESC) * size
            if tw <= w / k + 0.5 and th <= h / k + 0.5: break
            size -= 0.5
    lines = wrap_lines(text, size, w / k, wrap)
    lh = (ASC + DESC) * size * k
    total = lh * len(lines)
    va = t.get("m_VerticalAlignment", 256); ha = t.get("m_HorizontalAlignment", 1)
    ty = y if va == 256 else (y + h - total if va == 1024 else y + (h - total) / 2)
    c = col(t.get("m_fontColor")); bold = t.get("m_fontStyle", 0) & 1
    lay = Image.new("RGBA", (max(1, int(w + 4 * k + 200)), max(1, int(total + 4))), (0, 0, 0, 0))
    d = ImageDraw.Draw(lay)
    for i, line in enumerate(lines):
        lw = text_width(line, size) * k
        lx = 0 if ha in (1, 8, 16) else ((w - lw) if ha == 4 else (w - lw) / 2)
        cx = lx; base = i * lh + ASC * size * k
        for p, part in runs(line):
            f = font(p, size * k)
            d.text((cx + 100, base), part, font=f, fill=c, anchor="ls", stroke_width=1 if bold and p == F_MAIN and size * k > 14 else 0, stroke_fill=c)
            cx += f.getlength(part)
    composite(dst, lay, x - 100, ty)

def world(n, ox, oy, sc):
    """n의 화면 좌표 (left, top, w, h) - 화면 y는 아래로"""
    pvx = n.lo[0] + n.size[0] * n.pv[0]; pvy = n.lo[1] + n.size[1] * n.pv[1]
    wpx = ox + pvx * sc; wpy = oy + pvy * sc; s2 = sc * n.scale
    left = wpx - n.size[0] * n.pv[0] * s2; bottom = wpy - n.size[1] * n.pv[1] * s2
    return left, bottom, s2
def render(n, dst, ox, oy, sc, alpha=1.0):
    if not n.active: return
    cg = n.c("CanvasGroup")
    if cg and cg.get("m_Enabled", 1): alpha *= cg.get("m_Alpha", 1)
    if alpha <= 0.01: return
    left, bottom, s2 = world(n, ox, oy, sc)
    W, H = n.size[0] * s2, n.size[1] * s2
    k = s2 * S
    X, Y = left * S, (CH - (bottom + n.size[1] * s2)) * S
    w, h = int(round(W * S)), int(round(H * S))
    target = dst
    mask = n.c("Mask") or n.c("RectMask2D")
    if mask: target = Image.new("RGBA", dst.size, (0, 0, 0, 0))
    graphic_for_mask = None
    for comp in n.comps:
        if not comp.get("m_Enabled", 1): continue
        t = comp["type"]; g = None
        if w <= 0 or h <= 0: break
        if t in ("Image", "TranslucentImage") or (t == "ProceduralImage"):
            c = col(comp.get("m_Color"), alpha)
            if t == "ProceduralImage":
                r, corners = radius_of(n, W / s2, H / s2)
                bw = comp.get("borderWidth", 0)
                g = rrect_img(w, h, r * k, c, bw * k if bw else 0, corners)
                g = fill_crop(g, comp)
            elif t == "TranslucentImage":
                crop = BG_BLUR.crop((int(X), int(Y), int(X) + w, int(Y) + h)).convert("RGBA")
                tint_c = Image.new("RGBA", crop.size, c[:3] + (255,))
                g = Image.blend(crop, tint_c, 0.72); g.putalpha(int(c[3] * 0.94))
            else:
                if comp.get("_icon"): src = sprite_img(comp["_icon"]); r = {"border_L": 0, "border_R": 0, "border_B": 0, "border_T": 0, "ppu": 100}
                else:
                    nm = (comp.get("m_Sprite") or "").split(":", 1)[-1]
                    r = SPR.get(nm); src = sprite_img(os.path.join(ROOT, "Sprites", "UI", r["file"])) if r else None
                if src is None: g = Image.new("RGBA", (w, h), c)
                else:
                    if comp.get("m_Type") in (1, 2) and r and float(r["border_L"]) + float(r["border_T"]) > 0:
                        kk = 100.0 / float(r["ppu"]) / comp.get("m_PixelsPerUnitMultiplier", 1) * k
                        bl, bb, br, bt = (float(r[x]) for x in ("border_L", "border_B", "border_R", "border_T"))
                        g = nine(src, w, h, (bl * kk, bb * kk, br * kk, bt * kk, int(bl), int(bb), int(br), int(bt)), comp.get("m_FillCenter", 1))
                    elif comp.get("m_PreserveAspect"):
                        ar = src.width / src.height
                        gw, gh = (w, int(w / ar)) if w / h < ar else (int(h * ar), h)
                        g = Image.new("RGBA", (w, h), (0, 0, 0, 0))
                        g.paste(src.resize((max(1, gw), max(1, gh)), Image.LANCZOS), ((w - gw) // 2, (h - gh) // 2))
                    else: g = src.resize((w, h), Image.LANCZOS)
                    g = fill_crop(tint(g, c), comp)
            if mask: graphic_for_mask = g
            if mask and not mask.get("m_ShowMaskGraphic", 1): continue
            if c[3] == 0 and not n.c("TrueShadow"): continue
            ts = n.c("TrueShadow")
            if ts and ts.get("m_Enabled", 1) and ts.get("color", {}).get("a", 0) > 0:
                if ts.get("inset"):
                    if c[3] > 0: composite(target, g, X, Y)
                    composite(target, inset_glow(g if c[3] > 0 else Image.new("RGBA", g.size, (255, 255, 255, 255)), ts, k), X, Y)
                    continue
                gg = g if c[3] > 0 else None
                if gg is not None:
                    sh, dx, dy = shadow_of(gg, ts, k)
                    composite(target, sh, X + dx, Y + dy)
            if c[3] > 0: composite(target, g, X, Y)
        elif t == "TextMeshProUGUI":
            draw_text(target, n, X, Y, w, h, k)
    for ch in n.children:
        render(ch, target, left, bottom, s2, alpha)
    if mask:
        m = Image.new("L", dst.size, 0)
        if graphic_for_mask is not None: composite_l(m, graphic_for_mask.split()[3], X, Y)
        else: ImageDraw.Draw(m).rectangle([X, Y, X + w, Y + h], fill=255)
        target.putalpha(ImageChops.multiply(target.split()[3], m))
        dst.alpha_composite(target)
def composite_l(dst, a, x, y):
    tmp = Image.new("L", dst.size, 0); tmp.paste(a, (int(round(x)), int(round(y)))); dst.paste(ImageChops.lighter(dst, tmp))

# ---------------- 실행 중에 채워지는 내용 ----------------
def item(pred, n=0):
    c = [r for r in ITEMS if pred(r)]
    return c[min(n, len(c) - 1)] if c else None
def tags(r): return r["tags"].split("|")
def set_text(node, text):
    t = node.c("TextMeshProUGUI")
    if t: t["m_text"] = text
def loc_texts(root):
    for n in root.walk():
        tl = n.c("TextLocalizor"); t = n.c("TextMeshProUGUI")
        if tl and t:
            key = next((v for kk, v in tl.items() if "key" in kk.lower() and isinstance(v, str)), None)
            if key and key in KO: t["m_text"] = KO[key]
def fill_display(disp, it, count=None, durability=None, selected=False, show_name=False):
    """ItemDisplay 노드에 아이템을 넣는다"""
    for x in ("Highlight", "ShortcutIndicator", "SelectionIndicator", "DisabledIndicator", "InspectioningIndicator",
              "DurabilityZeroIndicator", "Hovering"):
        for n in disp.walk():
            if n.name == x: n.active = False
    for n in disp.walk():
        if n.name in ("Wishlisted", "BuildingRequired", "QuestRequired", "SlotIndicators"): n.active = False
    icon = disp.find("Icon"); im = icon.c("Image")
    if it is None:
        icon.active = False
        for n in disp.walk():
            if n.name in ("DurabilityContainer", "CountContainer", "NameContainer"): n.active = False
        return
    im["_icon"] = os.path.join(ROOT, "Sprites", "Items", it["icon"]); im["m_Sprite"] = None
    ts = icon.c("TrueShadow"); q = int(it["quality"])
    if ts:
        if q in QCOL: ts.update(color={"r": QCOL[q][0] / 255, "g": QCOL[q][1] / 255, "b": QCOL[q][2] / 255, "a": 1}, offsetDistance=0, size=3, spread=0.5)
        else: ts.update(color={"r": 0, "g": 0, "b": 0, "a": 0.72}, offsetDistance=8)
    for n in disp.walk():
        if n.name == "SelectionIndicator": n.active = selected
        if n.name == "CountContainer":
            n.active = count is not None
            if count is not None: set_text(n.find("Count"), str(count))
        if n.name == "DurabilityContainer":
            n.active = durability is not None
            if durability is not None:
                for x in n.children:
                    p = x.c("ProceduralImage")
                    if x.name == "Fill": p["m_FillAmount"] = durability
                    if x.name == "Loss": p["m_FillAmount"] = 0
        if n.name == "NameContainer":
            n.active = show_name
            if show_name: set_text(n.find("Text (TMP)"), it["name_ko"])
def make_entries(layout, prefab, contents, total, lock_from=None, selected_idx=None):
    layout.children = []
    for i in range(total):
        e = prefab.clone(layout); e.active = True
        it = contents[i] if i < len(contents) else None
        cnt = dur = None
        if it:
            if int(it["maxStack"]) > 1: cnt = min(int(it["maxStack"]), 7 + (i * 13) % 50)
            if "Repairable" in tags(it): dur = 0.35 + (i * 0.17) % 0.6
        fill_display(e.find("Main/ItemDisplay"), it, cnt, dur, selected=(i == selected_idx))
        e.find("Main/Locked").active = lock_from is not None and i >= lock_from
        layout.children.append(e)
def make_slots(grid, prefab, slots):
    grid.children = []
    for label, it in slots:
        s = prefab.clone(grid); s.active = True
        set_text(s.find("LabelContainer/Label"), label)
        s.find("ItemDisplayContainer/PluggableIndicator").active = False
        s.find("ItemDisplayContainer/Hovering").active = False
        disp = s.find("ItemDisplayContainer/ItemDisplay")
        if it:
            s.find("ItemDisplayContainer/SlotIcon").active = False
            fill_display(disp, it, durability=0.8 if "Repairable" in tags(it) else None)
        else: disp.active = False
        grid.children.append(s)

def build(scenario):
    tabs = N(load_json("01_Tabs.json"))
    root = N({"name": "GameplayUICanvas", "rect": {"anchorMin": [0, 0], "anchorMax": [0, 0], "pos": [0, 0], "size": [CW, CH], "pivot": [0, 0]}, "children": []})
    tabs.parent = root; root.children = [tabs]; tabs.active = True
    va = tabs.find("ViewArea")
    for v in va.children: v.active = v.name == "LootView"
    for b in tabs.find("ViewButtons").children:
        for x in b.children:
            if x.name in ("Hover", "BG"): x.active = False
            if x.name == "SelectionIndicator": x.active = b.name == "BackpackButton"
        if b.name == "BackpackButton":
            wb = b.find("WeightBar"); wb.find("Fill").c("ProceduralImage")["m_FillAmount"] = 0.42
            set_text(wb.find("Text (TMP)"), "")
    lv = va.find("LootView")
    entry = N(load_json("10_Prefab_InventoryEntry.json")); slotp = N(load_json("13_Prefab_SlotDisplay.json"))
    loc_texts(tabs); loc_texts(entry); loc_texts(slotp)

    pick = lambda f, i=0: item(f, i)
    gun = pick(lambda r: "GunType_AR" in tags(r) and r["quality"] == "4")
    pistol = pick(lambda r: "GunType_PST" in tags(r) and r["quality"] in ("2", "3"))
    melee = pick(lambda r: "MeleeWeapon" in tags(r) and r["quality"] == "3")
    helmet = pick(lambda r: "Helmat" in tags(r) and r["quality"] == "3")
    armor = pick(lambda r: "Armor" in tags(r) and r["quality"] == "4")
    bag = pick(lambda r: "Backpack" in tags(r) and r["quality"] == "3")
    slots = [("총기", gun), ("총기", pistol), (KO.get("Tag_MeleeWeapon", "근접 무기"), melee), (KO["Tag_Helmat"], helmet),
             (KO["Tag_Armor"], armor), ("마스크", None), ("헤드셋", None), (KO["Tag_Backpack"], bag), (KO["Tag_Totem"], None), (KO["Tag_Totem"], None)]
    eq = lv.find("Main/EquipmentAndInventory/Content")
    make_slots(eq.find("ItemSlotsDisplay/GridLayout"), slotp, slots)
    bag_items = [pick(lambda r: "Bullet" in tags(r) and r["quality"] == "2"), pick(lambda r: "Bullet" in tags(r) and r["quality"] == "3"),
                 pick(lambda r: "Medic" in tags(r) and r["quality"] == "2"), pick(lambda r: "Medic" in tags(r) and r["quality"] == "3"),
                 pick(lambda r: "Food" in tags(r) and r["quality"] == "1"), pick(lambda r: "Drink" in tags(r) and r["quality"] == "2"),
                 pick(lambda r: "Magazine" in tags(r) and r["quality"] == "3"), pick(lambda r: "Scope" in tags(r) and r["quality"] == "4"),
                 pick(lambda r: "Luxury" in tags(r) and r["quality"] == "5"), pick(lambda r: "Electric" in tags(r) and r["quality"] == "3"),
                 pick(lambda r: "Explosive" in tags(r)), pick(lambda r: "Key" in tags(r) and r["quality"] == "2"),
                 pick(lambda r: "Gem" in tags(r)), pick(lambda r: "Tool" in tags(r) and r["quality"] == "2"),
                 None, pick(lambda r: "Material" in tags(r) and r["quality"] == "1"), None, pick(lambda r: "Misc" in tags(r) and r["quality"] == "1")]
    inv = eq.find("Scroll View/Viewport/Content/InventoryDisplay")
    make_entries(inv.find("Container/Layout"), entry, bag_items, 30, lock_from=None, selected_idx=0 if scenario == "tab" else None)
    inv.find("Container/LoadingIndicator").active = False; inv.find("Container/PlaceHolder").active = False
    tb = inv.find("TitleBar (1)")
    set_text(tb.find("Text (TMP)"), KO["UI_InventoryDefault"]); set_text(tb.find("Text (TMP)_1"), f"({len([x for x in bag_items if x])}/30)")
    for b in ("StoreAllBtn",):
        try: tb.find(b).active = scenario == "loot"
        except KeyError: pass
    pet = eq.find("InventoryDisplay_Pet")
    make_entries(pet.find("Container/Layout"), entry, [], 3)
    pet.find("Container/LoadingIndicator").active = False; pet.find("Container/PlaceHolder").active = False
    wbc = eq.find("WeghtBarContainer")
    wb = wbc.find("WeightBar/BarArea")
    wb.find("BGAndMAsk/MainBar").sd[0] = 260
    for x in ("LightMark", "SuperHeavyMark"): wb.find(x).active = False
    set_text(wb.find("WeightBar/Text (TMP)"), "18.4/40kg")
    title = lv.find("Main/EquipmentAndInventory/Title")
    for n in title.walk():
        if n.name == "Text" and n.parent.name == "Money": set_text(n, "12,580")
        if n.name == "Text" and n.parent.name == "CashDisplay": set_text(n, "3,200")
    # 퀵슬롯 4칸
    sc = lv.find("Main/ShortcutEditor"); lay = sc.find("Layout"); tmpl = lay.children[0]; lay.children = []
    quick = [bag_items[2], bag_items[3], bag_items[10], None]
    for i in range(4):
        e = tmpl.clone(lay); e.find("Hovering").active = False
        fill_display(e.find("ItemDisplay"), quick[i], count=3 if quick[i] and int(quick[i]["maxStack"]) > 1 else None)
        set_text(e.find("InputIndicator/TextContainer/Text (TMP)"), str(i + 3))
        lay.children.append(e)
    # 루팅 대상
    lt = lv.find("Main/LootTarget")
    lt.active = scenario == "loot"
    if scenario == "loot":
        set_text(lt.find("Title/Text (TMP)"), KO.get("UI_LootBox_Explor", "자료함")); set_text(lt.find("Title/Capacity"), "(9/20)")
        ld = lt.find("Content/Scroll View/Viewport/Content/InventoryDisplay")
        loot = [pick(lambda r: "Gun" in tags(r) and r["quality"] == "2"), pick(lambda r: "Bullet" in tags(r) and r["quality"] == "1"),
                pick(lambda r: "Luxury" in tags(r) and r["quality"] == "3"), pick(lambda r: "Food" in tags(r) and r["quality"] == "2"),
                pick(lambda r: "Medic" in tags(r) and r["quality"] == "1"), pick(lambda r: "Electric" in tags(r) and r["quality"] == "4"),
                pick(lambda r: "Gem" in tags(r) and r["quality"] == "6"), pick(lambda r: "Material" in tags(r) and r["quality"] == "2"),
                pick(lambda r: "Helmat" in tags(r) and r["quality"] == "2")]
        make_entries(ld.find("Container/Layout"), entry, loot, 20)
        ld.find("Container/LoadingIndicator").active = False; ld.find("Container/PlaceHolder").active = False
        ltb = ld.find("TitleBar (1)"); ltb.active = False
        lt.find("Content/PagesControl").active = False
        fd = lt.find("Content/FilterDisplay"); fe = fd.children[0]; fd.children = []
        for i, ic in enumerate(["PictoIcon_Layer_2", "PictoIcon_Gun", "PictoIcon_Helmet", "PictoIcon_Backpack", "PictoIcon_Water", "PictoIcon_Gem"]):
            e = fe.clone(fd)
            for n in e.walk():
                if n.name == "Selected": n.active = i == 0
                if n.name == "Hover": n.active = False
                if n.name == "Icon": n.c("Image")["m_Sprite"] = "Sprite:" + ic; n.c("Image")["_icon"] = os.path.join(DUCKOV, "Resource_100", "Sprite", ic + ".png")
            fd.children.append(e)
    # 아이템 상세 (선택한 아이템)
    det = lv.find("ItemDetails")
    sel = bag_items[0] if scenario == "tab" else loot[0]
    det.active = True
    core = det.find("Panel/ItemDisplayCore")
    set_text(core.find("Name/ItemNameText"), sel["name_ko"])
    set_text(core.find("Extra/Weight/WeightText"), f"{float(sel['weight']):.2f}kg")
    core.find("Extra/UsableIndicator").active = False; core.find("Extra/RegisteredIndicator").active = False
    ic = core.find("Basics/IconContainer")
    ic.find("Icon").c("Image")["_icon"] = os.path.join(ROOT, "Sprites", "Items", sel["icon"])
    ic.find("CountContainer").active = int(sel["maxStack"]) > 1; set_text(ic.find("CountContainer/Count"), "7")
    ic.find("DurabilityDisplay").active = "Repairable" in tags(sel)
    set_text(core.find("Basics/Texts/Scroll View/Viewport/Content/ItemDescriptionText"), sel["desc_ko"] or sel["name_ko"])
    tg = core.find("Tags"); t0 = tg.children[0]; tg.children = []
    for tname in [x for x in tags(sel) if "Tag_" + x in KO][:4]:
        e = t0.clone(tg); set_text(e.find("Text (TMP)"), KO["Tag_" + tname]); tg.children.append(e)
    core.find("ItemSlotsDisplay").active = False
    for n in core.find("Stats And Effects (Scroll View)").walk():
        if n.name in ("UsageUtilitiesDisplay",): n.active = False
    core.find("Stats And Effects (Scroll View)").active = False
    set_text(core.find("ItemID"), "#" + sel["typeID"])
    return root, [bag_items, slots, sel]

def background():
    """게임 화면 대신 쓸 배경: 메인 메뉴 배경을 어둡게"""
    p = os.path.join(DUCKOV, "Resource_100", "Texture2D", "MainMenuBackground.png")
    im = Image.open(p).convert("RGB")
    W, H = int(CW * S), int(CH * S)
    s = max(W / im.width, H / im.height); im = im.resize((int(im.width * s), int(im.height * s)), Image.LANCZOS)
    im = im.crop(((im.width - W) // 2, (im.height - H) // 2, (im.width - W) // 2 + W, (im.height - H) // 2 + H))
    im = Image.blend(im, Image.new("RGB", im.size, (20, 26, 30)), 0.35)
    return im.convert("RGBA")

if __name__ == "__main__":
    for scen in (sys.argv[1:] or ["tab", "loot"]):
        BG = background(); BG_BLUR = BG.filter(ImageFilter.GaussianBlur(24 * S))
        root, info = build(scen)
        do_layout(root)
        out = BG.copy()
        render(root.children[0], out, 0, 0, 1.0)
        name = os.path.join(ROOT, f"preview_inventory_{scen}.png")
        out.convert("RGB").save(name)
        print("saved", name)
