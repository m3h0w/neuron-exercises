from os import name
from neuron import h, gui

# topology
NDEND = 1
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
soma.L = 30
soma.diam = 30
apical.L = 30
apical.diam = 5

for i in range(NDEND):
    ap[i].L = 15
    ap[i].diam = 2 
    oblique[i].L = 15+5*i
    oblique[i].diam = 1 

ps = h.PlotShape(True)
ps.show(0)
ps.exec_menu("View Axis")

#h.define_shape()      #not necessary if PlotShape is created

#for sec in h.allsec():
#   for i in range(sec.n3d()):
#       print(sec, sec.x3d(i), sec.y3d(i), sec.z3d(i), sec.diam3d(i))