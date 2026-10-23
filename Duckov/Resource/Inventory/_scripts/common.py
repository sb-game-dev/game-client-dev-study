import UnityPy, os, struct, json
from UnityPy.helpers.TypeTreeGenerator import TypeTreeGenerator
D=r"D:\STEAM\steamapps\common\Escape from Duckov\Duckov_Data"
HERE=os.path.dirname(os.path.abspath(__file__))
scripts={int(k):v for k,v in json.load(open(os.path.join(HERE,"scripts.json"))).items()}
gen=TypeTreeGenerator("2022.3.62f2"); gen.load_local_dll_folder(os.path.join(D,"Managed"))
def script_of(o):
    raw=o.get_raw_data(); fid,pid=struct.unpack_from("<iq",raw,16)
    if fid==0: return None
    if not o.assets_file.externals[fid-1].path.endswith("globalgamemanagers.assets"): return None
    return scripts.get(pid)
def read_mb(o):
    s=script_of(o)
    if not s: return None,None
    try:
        n=gen.get_nodes_up(s[0], (s[1]+"."+s[2]) if s[1] else s[2])
        return s,o.read_typetree(n)
    except Exception as e:
        return s,{"_error":str(e)}
