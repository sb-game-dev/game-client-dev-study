# 아이템 데이터(이름/등급/무게/가치/태그/용량) + 아이콘 + GameplayDataSettings
from common import *
import csv, re
OUT=r"C:\Users\cho99\source\repos\sb-game-dev\game-client-dev-study\Duckov\Resource\Inventory"
env=UnityPy.load(os.path.join(D,"resources.assets"))
af=list(env.files.values())[0]; objs=af.objects
def safe(n): return re.sub(r'[\\/:*?"<>|]',"_",n)
def loc(lang):
    m={}
    with open(os.path.join(D,"StreamingAssets","Localization",lang+".csv"),encoding="utf-8-sig",newline="") as f:
        for row in csv.reader(f):
            if len(row)>=2: m[row[0]]=re.sub(r"\\(.)",r"\1",row[1])
    return m
KO=loc("Korean"); EN=loc("English")

mb_cache={}
def mb(pid):
    if pid not in mb_cache:
        o=objs.get(pid); mb_cache[pid]=read_mb(o) if o is not None and o.type.name=="MonoBehaviour" else (None,None)
    return mb_cache[pid]
go={}
for o in objs.values():
    if o.type.name=="GameObject": go[o.path_id]=o
# 태그 이름
def tag_name(pid):
    s,d=mb(pid); return (d or {}).get("m_Name","?") if isinstance(d,dict) else "?"

ID=os.path.join(OUT,"Sprites","Items"); os.makedirs(ID,exist_ok=True)
rows={}; icon_saved={}
for o in objs.values():
    if o.type.name!="MonoBehaviour": continue
    s=script_of(o)
    if not s or s[2]!="Item": continue
    s,d=read_mb(o)
    if not isinstance(d,dict) or "_error" in d: continue
    gname=go[d["m_GameObject"]["m_PathID"]].read_typetree()["m_Name"]
    tid=d["typeID"]
    key=d["displayName"]
    tags=[tag_name(t["m_PathID"]) for t in d["tags"]["list"] if t["m_FileID"]==0]
    cap=""
    ip=d["inventory"]["m_PathID"]
    if ip:
        _,inv=mb(ip)
        if isinstance(inv,dict): cap=inv.get("defaultCapacity",inv.get("capacity",""))
    nslots=""
    sp=d["slots"]["m_PathID"]
    if sp:
        _,sc=mb(sp)
        if isinstance(sc,dict):
            lst=sc.get("list") or sc.get("slots") or []
            nslots=len(lst) if isinstance(lst,list) else ""
            slot_keys=[x.get("key","") for x in lst] if isinstance(lst,list) else []
        else: slot_keys=[]
    else: slot_keys=[]
    icon=""
    ipid=d["icon"]["m_PathID"]
    if ipid:
        so=objs.get(ipid) if d["icon"]["m_FileID"]==0 else None
        if so is not None:
            if ipid not in icon_saved:
                sd=so.read(); fn=f"{tid}_{safe(sd.m_Name)}.png"
                try: sd.image.save(os.path.join(ID,fn)); icon_saved[ipid]=fn
                except Exception as e: icon_saved[ipid]=""
            icon=icon_saved[ipid]
    row={"typeID":tid,"prefab":gname,"nameKey":key,"name_ko":KO.get(key,""),"name_en":EN.get(key,""),
         "quality":d["quality"],"displayQuality":d["displayQuality"],"value":d["value"],"weight":round(d["weight"],3),
         "maxStack":d["maxStackCount"],"inventoryCapacity":cap,"slots":nslots,"slotKeys":"|".join(slot_keys),
         "tags":"|".join(tags),"icon":icon,"order":d["order"],"desc_ko":KO.get(key+"_Desc","").replace("\n"," ")}
    if tid in rows and rows[tid]["icon"]: continue
    rows[tid]=row
cols=list(next(iter(rows.values())).keys())
with open(os.path.join(OUT,"items.csv"),"w",newline="",encoding="utf-8-sig") as f:
    w=csv.DictWriter(f,cols); w.writeheader(); w.writerows(sorted(rows.values(),key=lambda r:r["typeID"]))
print("items",len(rows),"icons",len([v for v in icon_saved.values() if v]))

# GameplayDataSettings (등급 색 등) 통째로
def clean(v):
    if isinstance(v,dict):
        if set(v)=={"m_FileID","m_PathID"}:
            if not v["m_PathID"]: return None
            if v["m_FileID"]==0:
                oo=objs.get(v["m_PathID"])
                if oo is None: return "ref"
                if oo.type.name=="MonoBehaviour":
                    s_,d_=mb(v["m_PathID"]); return f"{s_[2] if s_ else 'MB'}:{(d_ or {}).get('m_Name','') if isinstance(d_,dict) else ''}"
                try: return f"{oo.type.name}:{oo.peek_name()}"
                except Exception: return oo.type.name
            return f"ext({v['m_FileID']},{v['m_PathID']})"
        return {k:clean(x) for k,x in v.items() if k not in("m_Script","m_GameObject")}
    if isinstance(v,list): return [clean(x) for x in v]
    if isinstance(v,float): return round(v,4)
    return v
for o in objs.values():
    if o.type.name!="MonoBehaviour": continue
    s=script_of(o)
    if s and s[2]=="GameplayDataSettings":
        _,d=read_mb(o)
        json.dump(clean(d),open(os.path.join(HERE,"GameplayDataSettings.json"),"w",encoding="utf-8"),ensure_ascii=False,indent=1)
        print("settings saved")
