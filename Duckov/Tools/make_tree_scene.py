# trees.csv(유니티 지형 나무 배치) -> 맵툴/클라이언트 씬 파일(.bin)
#
# 씬 포맷 (CEditorUI::Save_Scene / CLevel::Load_Scene 과 동일)
#   uint32 개수
#   반복: uint32 길이, wchar[] 원형태그, float3 위치, float4 쿼터니언(xyzw), float3 스케일, uint32 길이, wchar[] 모델태그
#
# 좌표 변환 (CVIBuffer_Terrain 기준, Hill 월드행렬 = 항등)
#   CSV x,z : 지형 로컬 (0 ~ 640)       -> 엔진 x = x - 320, z = z - 320  (m_fHalfWidth / m_fHalfDepth)
#   CSV y   : 지형 로컬 높이 (raw*600)  -> 엔진 y = y - 30                (LoadHeightMap의 -30.f)
#   rotation_rad : Y축 회전 (유니티/DX 둘 다 왼손 좌표계라 부호 그대로)
#
# 사용법
#   python make_tree_scene.py                         -> 전체 나무
#   python make_tree_scene.py --radius 80             -> 플레이어 시작 위치 기준 80m 안쪽만
#   python make_tree_scene.py --model-tag Prototype_Component_Model_Tree_01   (Proto::Model_Tree_01 값을 바꿨다면)

import argparse, csv, math, os, struct

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "Resource")
CSV_PATH = os.path.join(ROOT, "Duckov_Extract", "Terrain", "Terrain_GroundZero_Crop", "trees.csv")

HALF_SIZE = 320.0       # (321 - 1) * 0.5 * 2.0
HEIGHT_OFFSET = -30.0
PLAYER_START = (38.2, -207.2)   # Level_GamePlay의 Player_Desc.vPosition

def write_wstr(f, s):
    f.write(struct.pack("<I", len(s)))
    f.write(s.encode("utf-16le"))

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", default=None)
    ap.add_argument("--radius", type=float, default=0.0, help="0이면 전체")
    ap.add_argument("--proto-tag", default="Prototype_GameObject_StaticProp")
    ap.add_argument("--model-tag", default="mesh/tree/pfb_tree_01_1.bin")
    args = ap.parse_args()

    trees = []
    with open(CSV_PATH, newline="") as f:
        for r in csv.DictReader(f):
            x = float(r["x"]) - HALF_SIZE
            z = float(r["z"]) - HALF_SIZE
            y = float(r["y"]) + HEIGHT_OFFSET
            if args.radius > 0 and math.hypot(x - PLAYER_START[0], z - PLAYER_START[1]) > args.radius:
                continue
            half = float(r["rotation_rad"]) * 0.5
            quat = (0.0, math.sin(half), 0.0, math.cos(half))     # XMQuaternionRotationRollPitchYaw(0, rot, 0)
            ws, hs = float(r["widthScale"]), float(r["heightScale"])
            trees.append(((x, y, z), quat, (ws, hs, ws)))

    out = args.out or os.path.join(ROOT, "SceneData",
                                   f"Trees_R{int(args.radius)}.bin" if args.radius > 0 else "Trees_All.bin")
    with open(out, "wb") as f:
        f.write(struct.pack("<I", len(trees)))
        for pos, quat, scale in trees:
            write_wstr(f, args.proto_tag)
            f.write(struct.pack("<3f", *pos))
            f.write(struct.pack("<4f", *quat))
            f.write(struct.pack("<3f", *scale))
            write_wstr(f, args.model_tag)

    print(f"{len(trees)} trees -> {os.path.normpath(out)}")

if __name__ == "__main__":
    main()
