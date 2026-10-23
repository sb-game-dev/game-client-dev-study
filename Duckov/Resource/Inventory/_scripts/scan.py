import UnityPy, os, struct, json, sys
from collections import Counter, defaultdict
D=r"D:\STEAM\steamapps\common\Escape from Duckov\Duckov_Data"
UnityPy.config.FALLBACK_UNITY_VERSION=None
g=UnityPy.load(os.path.join(D,"globalgamemanagers.assets"))
scripts={}
for o in g.objects:
    if o.type.name=="MonoScript":
        d=o.read()
        scripts[o.path_id]=(d.m_AssemblyName,d.m_Namespace,d.m_ClassName)
print("scripts",len(scripts), g.objects[0].assets_file.unity_version)
json.dump({k:v for k,v in scripts.items()},open(os.path.join(os.path.dirname(__file__),"scripts.json"),"w"))
want=("Inventory","Slot","ItemDisplay","ItemOperation","Stash","Loot","Equipment","Weight","Tooltip","ItemDetail")
res=defaultdict(Counter)
files=[f for f in os.listdir(D) if (f.startswith("level") or f.startswith("sharedassets") or f=="resources.assets") and not f.endswith(".resS")]
for f in sorted(files):
    env=UnityPy.load(os.path.join(D,f))
    for af in env.files.values():
        if not hasattr(af,"objects"): continue
        ext=af.externals
        for o in af.objects.values():
            if o.type.name!="MonoBehaviour": continue
            raw=o.get_raw_data()
            fid,pid=struct.unpack_from("<iq",raw,16)
            if fid==0: continue
            if not ext[fid-1].path.endswith("globalgamemanagers.assets"): continue
            s=scripts.get(pid)
            if s and any(w in s[2] for w in want): res[f][s[2]]+=1
    if res[f]: print(f, dict(res[f])); sys.stdout.flush()
