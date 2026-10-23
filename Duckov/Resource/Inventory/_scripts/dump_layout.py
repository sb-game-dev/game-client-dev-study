# Duckov 인벤토리 UI 레이아웃 덤프
from common import *
import math, pickle
OUT=r"C:\Users\cho99\source\repos\sb-game-dev\game-client-dev-study\Duckov\Resource\Inventory"
os.makedirs(OUT,exist_ok=True)
env=UnityPy.load(os.path.join(D,"resources.assets"))
af=list(env.files.values())[0]; objs=af.objects
ext_cache={}
def ext_file(name):
    b=os.path.basename(name)
    if b in ext_cache: return ext_cache[b]
    f=None
    for c in (os.path.join(D,b), os.path.join(D,"Resources",b)):
        if os.path.exists(c):
            e=UnityPy.load(c); f=[x for x in e.files.values() if hasattr(x,"objects")][0]; break
    ext_cache[b]=f; return f
def deref(fid,pid,base=af):
    if pid==0: return None
    f=base if fid==0 else ext_file(base.externals[fid-1].path)
    if f is None: return None
    return f.objects.get(pid)

tr={};go={}
for o in objs.values():
    if o.type.name in("Transform","RectTransform"): tr[o.path_id]=(o,o.read_typetree())
    elif o.type.name=="GameObject": go[o.path_id]=o.read_typetree()
go_tr={d["m_GameObject"]["m_PathID"]:p for p,(o,d) in tr.items()}
def path_of_tr(tp):
    p=[]
    while tp:
        o,d=tr[tp]; p.append(go[d["m_GameObject"]["m_PathID"]]["m_Name"]); tp=d["m_Father"]["m_PathID"]
    return "/".join(reversed(p))
path_to_tr={}
for tp in tr: path_to_tr.setdefault(path_of_tr(tp),tp)

used_sprites={}
DROP={"m_GameObject","m_Script","m_OnCullStateChanged","m_ObjectHideFlags","m_CorrespondingSourceObject","m_PrefabInstance","m_PrefabAsset","m_fontSharedMaterials","m_fontMaterials","m_textInfo","m_havePropertiesChanged","m_isInputParsingRequired","m_inputSource"}
name_cache={}
def name_of(o):
    k=(o.assets_file.name,o.path_id)
    if k in name_cache: return name_cache[k]
    try:
        if o.type.name=="MonoBehaviour":
            s=script_of(o); n=""
            if s:
                try: n=o.read_typetree(gen.get_nodes_up(s[0],(s[1]+"."+s[2]) if s[1] else s[2])).get("m_Name","")
                except Exception: pass
            r=f"{s[2] if s else 'MonoBehaviour'}:{n}"
        elif o.type.name in("Transform","RectTransform") and o.assets_file is af: r="Transform:"+path_of_tr(o.path_id)
        else:
            try: n=o.peek_name()
            except Exception: n=None
            if n is None:
                try: n=o.read_typetree().get("m_Name","")
                except Exception: n="?"
            r=f"{o.type.name}:{n}"
    except Exception: r=f"{o.type.name}:?"
    name_cache[k]=r; return r
cur_path=[None]
def clean(v):
    if isinstance(v,dict):
        if set(v.keys())=={"m_FileID","m_PathID"}:
            if v["m_PathID"]==0: return None
            o=deref(v["m_FileID"],v["m_PathID"])
            if o is None: return f"ref({v['m_FileID']},{v['m_PathID']})"
            if o.type.name=="Sprite":
                used_sprites.setdefault((os.path.basename(o.assets_file.name),o.path_id),set()).add(cur_path[0])
            if o.type.name=="GameObject" and o.assets_file is af: return "GameObject:"+path_of_tr(go_tr[o.path_id])
            return name_of(o)
        return {k:clean(x) for k,x in v.items() if k not in DROP}
    if isinstance(v,list):
        if len(v)>64: return [clean(x) for x in v[:64]]+[f"...(+{len(v)-64})"]
        return [clean(x) for x in v]
    if isinstance(v,float): return round(v,4)
    return v
def comp_info(cp):
    o=objs.get(cp)
    if o is None: return None
    t=o.type.name
    if t in("Transform","RectTransform","CanvasRenderer"): return None
    if t=="MonoBehaviour":
        s,d=read_mb(o)
        if s is None: return {"type":"MonoBehaviour(?)"}
        if not isinstance(d,dict) or "_error" in d: return {"type":s[2],"_error":str(d)}
        r={"type":s[2],"ns":s[1]}
    else:
        try: d=o.read_typetree()
        except Exception as e: return {"type":t,"_error":str(e)}
        r={"type":t}
    r.update(clean(d)); return r
def node(tp,depth=None):
    o,d=tr[tp]; g=go[d["m_GameObject"]["m_PathID"]]
    cur_path[0]=path_of_tr(tp)
    n={"name":g["m_Name"],"active":bool(g["m_IsActive"])}
    if o.type.name=="RectTransform":
        f=lambda v:[round(v["x"],2),round(v["y"],2)]
        n["rect"]={"anchorMin":f(d["m_AnchorMin"]),"anchorMax":f(d["m_AnchorMax"]),"pos":f(d["m_AnchoredPosition"]),"size":f(d["m_SizeDelta"]),"pivot":f(d["m_Pivot"])}
        sc=d["m_LocalScale"]
        if (round(sc["x"],3),round(sc["y"],3),round(sc["z"],3))!=(1,1,1): n["rect"]["scale"]=[round(sc["x"],3),round(sc["y"],3),round(sc["z"],3)]
        q=d["m_LocalRotation"]
        if abs(q["w"])<0.9999: n["rect"]["rotZ_deg"]=round(math.degrees(2*math.atan2(q["z"],q["w"])),2)
    else: n["transform"]="Transform(not UI)"
    n["components"]=[c for c in (comp_info(c["component"]["m_PathID"]) for c in g["m_Component"]) if c]
    if depth==0: n["children"]=[{"name":go[tr[ch["m_PathID"]][1]["m_GameObject"]["m_PathID"]]["m_Name"],"note":"omitted"} for ch in d["m_Children"]]
    else: n["children"]=[node(ch["m_PathID"],None if depth is None else depth-1) for ch in d["m_Children"]]
    return n

def hexcol(c):
    if not isinstance(c,dict): return str(c)
    return "#%02X%02X%02X%02X"%tuple(int(round(max(0,min(1,c[k]))*255)) for k in "rgba")
IMGTYPE={0:"Simple",1:"Sliced",2:"Tiled",3:"Filled"}
def v2(v): return f"{v['x']:g}x{v['y']:g}" if isinstance(v,dict) else str(v)
def brief(c):
    t=c["type"]
    try:
        if t=="Image":
            s=f"Image[{c.get('m_Sprite') or 'none'} {IMGTYPE.get(c.get('m_Type'),c.get('m_Type'))} {hexcol(c.get('m_Color'))}"
            if c.get("m_Type")==3: s+=f" fill={c.get('m_FillAmount')} method={c.get('m_FillMethod')}"
            if c.get("m_PixelsPerUnitMultiplier",1)!=1: s+=f" ppuMul={c.get('m_PixelsPerUnitMultiplier')}"
            if c.get("m_PreserveAspect"): s+=" preserveAspect"
            if c.get("m_Material"): s+=f" mat={c.get('m_Material')}"
            return s+("" if c.get("m_Enabled",1) else " (disabled)")+"]"
        if t=="ProceduralImage":
            bw=c.get("borderWidth",0)
            s=f"ProceduralImage[{'outline '+format(bw,'g')+'px' if bw else 'filled'} {hexcol(c.get('m_Color'))} falloff={c.get('falloffDistance')}"
            if c.get("m_Type")==3: s+=f" fill={c.get('m_FillAmount')} method={c.get('m_FillMethod')} origin={c.get('m_FillOrigin')}"
            return s+("" if c.get("m_Enabled",1) else " (disabled)")+"]"
        if t=="UniformModifier": return f"  └ 모서리 radius={c.get('radius')}"
        if t=="RoundModifier": return "  └ 모서리 radius=짧은 변/2 (알약 모양)"
        if t=="FreeModifier":
            r=c.get("radius"); return f"  └ 모서리 radius(좌상,우상,우하,좌하)=({r['x']:g},{r['y']:g},{r['z']:g},{r['w']:g})" if isinstance(r,dict) else "  └ FreeModifier"
        if t=="OnlyOneEdgeModifier": return f"  └ 한쪽 변만 둥글게 radius={c.get('radius')} side={c.get('side')}"
        if t=="TrueShadow":
            o=c.get("offset") or {}
            return f"TrueShadow[{'inset(안쪽 글로우)' if c.get('inset') else 'drop'} size={c.get('size')} spread={c.get('spread')} {hexcol(c.get('color'))} angle={c.get('offsetAngle')} dist={c.get('offsetDistance')} blend={c.get('blendMode')}]"
        if t=="UIGradient": return "UIGradient["+", ".join(f"{k}={hexcol(v) if isinstance(v,dict) and 'r' in v else v}" for k,v in c.items() if k not in("type","ns","m_Enabled","m_Name"))[:200]+"]"
        if t=="TranslucentImage": return f"TranslucentImage[블러 배경 {hexcol(c.get('m_Color'))} vibrancy={c.get('vibrancy')} brightness={c.get('brightness')} flatten={c.get('flatten')}]"
        if t=="InventoryDisplay": return "InventoryDisplay["+", ".join(f"{k}={v}" for k,v in c.items() if k not in("type","ns","m_Enabled","m_Name") and not isinstance(v,(dict,list)))[:300]+"]"
        if t=="RawImage": return f"RawImage[{c.get('m_Texture')} {hexcol(c.get('m_Color'))}]"
        if t in("TextMeshProUGUI","Text"):
            txt=(c.get("m_text") or c.get("m_Text") or "").replace("\n","\\n")[:40]
            return f"Text[\"{txt}\" size={c.get('m_fontSize')} {hexcol(c.get('m_fontColor'))} font={c.get('m_fontAsset')} hAlign={c.get('m_HorizontalAlignment')} vAlign={c.get('m_VerticalAlignment')} autoSize={c.get('m_enableAutoSizing')}]"
        if t=="GridLayoutGroup":
            p=c["m_Padding"]; return f"Grid[cell={v2(c['m_CellSize'])} spacing={v2(c['m_Spacing'])} pad(L{p['m_Left']} R{p['m_Right']} T{p['m_Top']} B{p['m_Bottom']}) constraint={c['m_Constraint']}:{c['m_ConstraintCount']} startCorner={c['m_StartCorner']} startAxis={c['m_StartAxis']} align={c['m_ChildAlignment']}]"
        if t in("HorizontalLayoutGroup","VerticalLayoutGroup"):
            p=c["m_Padding"]; return f"{t[:-11]}Layout[spacing={c['m_Spacing']} pad(L{p['m_Left']} R{p['m_Right']} T{p['m_Top']} B{p['m_Bottom']}) align={c['m_ChildAlignment']} ctrl(w{c['m_ChildControlWidth']} h{c['m_ChildControlHeight']}) expand(w{c['m_ChildForceExpandWidth']} h{c['m_ChildForceExpandHeight']})]"
        if t=="LayoutElement":
            return "LayoutElement["+" ".join(f"{k[2:]}={c[k]}" for k in("m_IgnoreLayout","m_MinWidth","m_MinHeight","m_PreferredWidth","m_PreferredHeight","m_FlexibleWidth","m_FlexibleHeight") if c.get(k) not in(None,-1,0))+"]"
        if t=="ContentSizeFitter": return f"ContentSizeFitter[h={c['m_HorizontalFit']} v={c['m_VerticalFit']}]"
        if t=="CanvasScaler": return f"CanvasScaler[mode={c['m_UiScaleMode']} ref={v2(c['m_ReferenceResolution'])} match={c['m_MatchWidthOrHeight']}]"
        if t=="CanvasGroup": return f"CanvasGroup[alpha={c.get('m_Alpha')}]"
        if t=="ScrollRect": return f"ScrollRect[h={c.get('m_Horizontal')} v={c.get('m_Vertical')}]"
        if t in("Outline","Shadow"): return f"{t}[{hexcol(c.get('m_EffectColor'))} {v2(c.get('m_EffectDistance'))}]"
        if t=="TextLocalizor":
            k=[v for kk,v in c.items() if "key" in kk.lower()]
            return f"TextLocalizor[{k[0] if k else ''}]"
    except Exception as e: return t+"(!"+str(e)+")"
    return t

TARGETS={
 "00_GameplayUICanvas_root":("LevelManager/GameplayUICanvas",0),
 "01_Tabs":("LevelManager/GameplayUICanvas/Tabs",None),
 "02_InventoryView":("LevelManager/GameplayUICanvas/Tabs/ViewArea/InventoryView",None),
 "03_LootView":("LevelManager/GameplayUICanvas/Tabs/ViewArea/LootView",None),
 "04_ItemDetails_Panel":("LevelManager/GameplayUICanvas/ItemDetails",None),
 "05_ItemOperationMenu":("LevelManager/GameplayUICanvas/ItemOperationMenu",None),
 "06_Tooltips":("LevelManager/GameplayUICanvas/Tooltips",None),
 "10_Prefab_InventoryEntry":("InventoryEntry",None),
 "11_Prefab_InventoryEntry_Trading_Selling":("InventoryEntry Trading Selling",None),
 "12_Prefab_ItemDisplay":("ItemDisplay",None),
 "13_Prefab_SlotDisplay":("SlotDisplay",None),
 "14_Prefab_SlotIndicator":("SlotIndicator",None),
 "15_Prefab_ItemPickerEntry":("ItemPickerEntry",None),
}
LD=os.path.join(OUT,"Layout"); os.makedirs(LD,exist_ok=True)
def wt(n,f,d=0):
    if "note" in n: f.write("  "*d+n["name"]+"  (하위 생략)\n"); return
    r=n.get("rect")
    rs=(f"  a{r['anchorMin']}-{r['anchorMax']} pos{r['pos']} size{r['size']} pv{r['pivot']}"+(f" scale{r['scale']}" if "scale" in r else "")+(f" rotZ{r['rotZ_deg']}" if "rotZ_deg" in r else "")) if r else ""
    f.write("  "*d+("" if n["active"] else "(off) ")+n["name"]+rs+"\n")
    for c in n["components"]: f.write("  "*d+"    · "+brief(c)+"\n")
    for ch in n["children"]: wt(ch,f,d+1)
for key,(p,depth) in TARGETS.items():
    tp=path_to_tr.get(p)
    if tp is None: print("NOT FOUND",p); continue
    n=node(tp,depth); n["_path"]=p
    json.dump(n,open(os.path.join(LD,key+".json"),"w",encoding="utf-8"),ensure_ascii=False,indent=1)
    with open(os.path.join(LD,key+".txt"),"w",encoding="utf-8") as f:
        f.write(f"# {p}\n# a[anchorMin]-[anchorMax] pos=anchoredPosition size=sizeDelta pv=pivot  (유니티 UI 좌표, y-up, 단위 = 캔버스 픽셀)\n\n"); wt(n,f)
    print("dumped",key)
pickle.dump({k:sorted(v) for k,v in used_sprites.items()},open(os.path.join(HERE,"used_sprites.pkl"),"wb"))
print("used sprites",len(used_sprites))
