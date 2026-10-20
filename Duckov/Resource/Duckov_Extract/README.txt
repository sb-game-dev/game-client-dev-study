Escape from Duckov 원본 데이터(Duckov_Data)에서 UnityPy로 추출한 리소스 (2026-10-19)
프로젝트 Resource / Resource_100 에 없던 것만 모음. 개인 학습용, 저장소/배포 금지.

Normal\          노멀맵 원본 (유니티 DXT5nm 패킹: R=1, G=Y, A=X → 그대로 쓰면 안 됨)
Normal_RGB\      위를 일반 탄젠트 노멀맵(RGB, 보라색)으로 변환한 사본 → 루나 18장용은 이것
Height\          Sand_height.png (반복되는 모래 물결 높이맵)
Terrain\<이름>\   지형 18개 (루나 19장)
   height_NxN_16bit.raw            값/65535 * 600 = 높이(m), [z][x] 순서, little-endian
   height_NxN_8bit_normalized.raw  0..255 → info.json의 heightMin_m..heightMax_m
   height_preview.png              높이 미리보기(정규화)
   splat_0.png                     블렌드맵 RGBA = layers[0..3] 가중치 (_rgb_preview는 보기용)
   ※ 방향 주의: .raw는 0행 = z 최소(남쪽, 유니티 배열 순서), .png들은 0행 = z 최대(북쪽, 이미지 순서)로 서로 상하 반대
   trees.csv                       나무 배치 (지형 원점 기준 m 좌표, 회전 rad)
   info.json                       크기, 레이어 텍스처 이름/타일 크기, 씬 배치 위치
Cubemap\<이름>\   큐브맵 11개 (루나 17장): 면 6장 PNG + cross_preview + <이름>.dds (RGBA8 큐브맵, 밉 없음)
                 rosendal_mountain / HDR_Deserts_01 / *_sky = 하늘, ReflectionProbe-* = 반사용 환경맵
Texture2D_Missing\  나머지 텍스처 338장 (MMOR/Metallic 마스크, 라이트맵 LDR_*, stbn 블루노이즈, AreaTex(SMAA) 등)
Mesh_Missing\       누락 메시 3개 (OBJ)
Sound\              FMOD Master.bank의 사운드 568개(WAV, 48kHz, vgmstream r2117로 추출) + 배경음악 mp3 1곡
                    같은 이름이 여러 개인 사운드는 "<이름>__<스트림번호>.wav" 로 구분
Terrain\Terrain_GroundZero_Crop\  제로존에서 실제 맵 영역만 자른 버전 (321x321, 640m x 640m, 원본 x 80~720m / z 0~640m)
                    배치 오프셋과 월드 위치는 info.json의 cropOffset_m / worldPosition_unity 참고
Scene\<번호>_<씬>\  씬 배치 (유니티 월드 좌표)
   props.csv                       메시(MeshRenderer) 배치
   lights.csv                      조명
   decals.csv                      URP DecalProjector 배치 (14_Level_GroundZero_1만, 2026-10-20)
                                   cx/cy/cz = 투영 박스 중심(오프셋 반영), width/height = 데칼 크기, depth = 투영 깊이
                                   right/up/fwd = 데칼 로컬 축(fwd 방향으로 투영, 바닥 데칼은 fwd_y = -1)
                                   데칼 UV = uv * uv_scale + uv_bias (아틀라스 일부 영역)
