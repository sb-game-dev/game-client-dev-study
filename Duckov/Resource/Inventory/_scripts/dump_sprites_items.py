# 인벤토리 UI 스프라이트(9-slice) + 아이템 데이터/아이콘 추출
from common import *
import csv, pickle, re
OUT=r"C:\Users\cho99\source\repos\sb-game-dev\game-client-dev-study\Duckov\Resource\Inventory"
used=pickle.load(open(os.path.join(HERE,"used_sprites.pkl"),"rb"))
files={}
def F(name):
    if name not in files:
        e=UnityPy.load(os.path.join(D,name)); files[name]=[x for x in e.files.values() if hasattr(x,"objects")][0]
    return files[name]
def safe(n): return re.sub(r'[\\/:*?"<>|]',"_",n)

def sprite_row(o):
    d=o.read()
    r=d.m_Rect; b=d.m_Border; p=d.m_Pivot
    return d,{"name":d.m_Name,"w":int(round(r.width)),"h":int(round(r.height)),
        "border_L":round(b.x,2),"border_B":round(b.y,2),"border_R":round(b.z,2),"border_T":round(b.w,2),
        "pivot_x":round(p.x,3),"pivot_y":round(p.y,3),"ppu":round(d.m_PixelsToUnits,2)}

# 1) 인벤토리 UI가 참조하는 스프라이트
SD=os.path.join(OUT,"Sprites","UI"); os.makedirs(SD,exist_ok=True)
rows=[]
names_used=set()
for (fn,pid),paths in sorted(used.items(),key=lambda x:str(x)):
    o=F(fn).objects[pid]
    d,row=sprite_row(o)
    fname=safe(d.m_Name)
    if fname in names_used: fname+=f"_{pid}"
    names_used.add(fname)
    try: d.image.save(os.path.join(SD,fname+".png"))
    except Exception as e: print("img fail",d.m_Name,e)
    row["file"]=fname+".png"; row["source"]=f"{fn}#{pid}"
    short=sorted({"/".join(p.split("/")[-3:]) for p in paths if p})
    row["used_count"]=len(paths); row["used_at(예시)"]=" | ".join(short[:4])
    rows.append(row)
cols=["file","name","w","h","border_L","border_B","border_R","border_T","pivot_x","pivot_y","ppu","used_count","used_at(예시)","source"]
with open(os.path.join(OUT,"Sprites","ui_sprites_9slice.csv"),"w",newline="",encoding="utf-8-sig") as f:
    w=csv.DictWriter(f,cols); w.writeheader(); w.writerows(rows)
print("ui sprites",len(rows))

# 2) 게임 전체 스프라이트 중 9-slice 값(border)이 있는 것 전부
allrows=[]
for fn in ("resources.assets","sharedassets0.assets"):
    for o in F(fn).objects.values():
        if o.type.name!="Sprite": continue
        d,row=sprite_row(o)
        if any(row[k] for k in("border_L","border_B","border_R","border_T")):
            row["source"]=f"{fn}#{o.path_id}"; allrows.append(row)
with open(os.path.join(OUT,"Sprites","all_sliced_sprites_9slice.csv"),"w",newline="",encoding="utf-8-sig") as f:
    w=csv.DictWriter(f,["name","w","h","border_L","border_B","border_R","border_T","pivot_x","pivot_y","ppu","source"]); w.writeheader(); w.writerows(sorted(allrows,key=lambda r:r["name"].lower()))
print("all sliced",len(allrows))
