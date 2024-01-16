from os import name
from neuron import h, gui

# topology
NDEND = 10
soma  = h.Section(name = "soma")
apical  = h.Section(name = "apical")

ap = []
oblique = []
for i in range(NDEND):
    ap.append(h.Section(name  = "ap[%g]" %i))
    oblique.append(h.Section(name  = "oblique[%g]" %i))

apical.connect(soma)
ap[0].connect(apical)  
oblique[0].connect(apical)  

for i in range(1, NDEND):
    ap[i].connect(ap[i-1])
    oblique[i].connect(ap[i-1])

# geometry 
soma.pt3dclear()
soma.pt3dadd(0, 0, 0, 30)
soma.pt3dadd(30, 0, 0, 30)
apical.pt3dclear()
apical.pt3dadd(0, 0, 0, 5)
apical.pt3dadd(30, 0, 0, 5)

for i in range(NDEND):
    ap[i].pt3dclear()
    ap[i].pt3dadd(0, 0, 0, 2)
    ap[i].pt3dadd(15, 0, 0, 2)
    oblique[i].pt3dclear()
    oblique[i].pt3dadd(0, 0, 0, 1)
    oblique[i].pt3dadd(0, 15+5*i, 0, 1)


ps = h.PlotShape(True)
ps.show(0)
ps.exec_menu("View Axis")

#h.define_shape()      #not necessary if PlotShape is created
for sec in h.allsec():
    for i in range(sec.n3d()):
        print(sec, sec.x3d(i), sec.y3d(i), sec.z3d(i), sec.diam3d(i))