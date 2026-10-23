# 추출 값으로 인벤토리 그리드(5열, 120x120 셀) 재구성 미리보기
import csv, os, json
from PIL import Image, ImageDraw, ImageFilter
I=r"C:\Users\cho99\source\repos\sb-game-dev\game-client-dev-study\Duckov\Resource\Inventory"
HERE=os.path.dirname(os.path.abspath(__file__))
u=json.load(open(os.path.join(HERE,"uiStyle.json"),encoding="utf-8"))
QC={q["quality"]:tuple(int(round(q["shadowColor"][k]*255)) for k in "rgb") for q in u["displayQualityLooks"]}
with open(os.path.join(I,"quality_colors.csv"),"w",newline="",encoding="utf-8-sig") as f:
    w=csv.writer(f); w.writerow(["quality","hex","r","g","b","shadowOffset","innerGlow","note"])
    for q in u["displayQualityLooks"]:
        c=q["shadowColor"]; rgb=[int(round(c[k]*255)) for k in "rgb"]
        w.writerow([q["quality"],"#%02X%02X%02X"%tuple(rgb),*[round(c[k],4) for k in "rgb"],q["shadowOffset"],q["innerGlow"],""])
    c=u["defaultDisplayQualityShadowColor"]
    w.writerow(["default","#%02X%02X%02X%02X"%tuple(int(round(c[k]*255)) for k in "rgba"),round(c["r"],4),round(c["g"],4),round(c["b"],4),u["defaultDisplayQualityShadowOffset"],u["defaultDIsplayQualityShadowInnerGlow"],"표에 없는 등급(0, 7 이상): 검정 72% 그림자, 오프셋 8"])

items=[r for r in csv.DictReader(open(os.path.join(I,"items.csv"),encoding="utf-8-sig")) if r["icon"]]
pick=[]
for q in ["1","2","3","4","5","6"]:
    pick+= [r for r in items if r["quality"]==q][:3]
pick=pick[:15]
S=2  # 2배로 그려서 축소(안티에일리어싱)
cell,pad=120,(4,8)
W,H=pad[0]*2+cell*5, pad[1]*2+cell*3
img=Image.new("RGBA",(W*S,H*S),(52,58,66,255))
def rrect(layer,box,r,fill=None,outline=None,width=0):
    d=ImageDraw.Draw(layer); d.rounded_rectangle([v*S for v in box],radius=r*S,fill=fill,outline=outline,width=width*S)
for i,r in enumerate(pick):
    cx=pad[0]+(i%5)*cell; cy=pad[1]+(i//5)*cell
    x0,y0,x1,y1=cx+4,cy+4,cx+cell-4,cy+cell-4   # ItemDisplay = 셀 - 8
    lay=Image.new("RGBA",img.size,(0,0,0,0))
    rrect(lay,(x0,y0,x1,y1),16,fill=(0,0,0,0x33))            # BG
    rrect(lay,(x0,y0,x1,y1),16,outline=(255,255,255,0x4C),width=2)  # Frame
    img.alpha_composite(lay)
    ic=Image.open(os.path.join(I,"Sprites","Items",r["icon"])).convert("RGBA")
    bw,bh=(x1-x0)*S,(y1-y0)*S; ic.thumbnail((bw,bh),Image.LANCZOS)
    px,py=int(x0*S+(bw-ic.width)/2),int(y0*S+(bh-ic.height)/2)
    q=int(r["quality"]); col=QC.get(q)
    a=ic.split()[3]
    if col:
        glow=Image.new("RGBA",ic.size,col+(0,)); glow.putalpha(a.filter(ImageFilter.MaxFilter(3)).filter(ImageFilter.GaussianBlur(3*S)))
        img.alpha_composite(glow,(px,py)); img.alpha_composite(glow,(px,py))
    else:
        sh=Image.new("RGBA",ic.size,(0,0,0,0)); sh.putalpha(a.point(lambda v:int(v*0.72)).filter(ImageFilter.GaussianBlur(3*S)))
        img.alpha_composite(sh,(px+int(6*S),py+int(6*S)))
    img.alpha_composite(ic,(px,py))
img=img.resize((W,H),Image.LANCZOS)
img.save(os.path.join(I,"preview_inventory_grid.png")); print("saved",W,H,[p["name_ko"] for p in pick])
