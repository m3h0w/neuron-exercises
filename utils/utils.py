def get_attributes(obj):
    print(", ".join(item for item in dir(obj) if not item.startswith("__")))

def get3d(h):
    h.define_shape()      #not necessary if PlotShape is created    

    for sec in h.allsec():
        for i in range(sec.n3d()):
            print(sec, sec.x3d(i), sec.y3d(i), sec.z3d(i), sec.diam3d(i))