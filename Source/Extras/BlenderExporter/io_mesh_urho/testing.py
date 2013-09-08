
PRINTMASK_COORD     = 0x0001
PRINTMASK_NORMAL    = 0x0002
PRINTMASK_UV        = 0x0004
PRINTMASK_TANGENT   = 0x0008
PRINTMASK_WEIGHT    = 0x0010

def PrintUrhoData(data, mask):
    print()
    for model in data.models:
        print("Model: " + model.name)        
        for ivb,vb in enumerate(model.vertexBuffers):
            print(" Vertex buffer {:d}".format(ivb) )
            print("  Mask: 0x{:X}".format(vb.elementMask) )
            for iv,v in enumerate(vb.vertices):
                print("  Vertex {:d}".format(iv) )
                if mask & PRINTMASK_COORD:
                    print("    Coord: {:+.3f} {:+.3f} {:+.3f}".format(v.pos.x, v.pos.y, v.pos.z) )
                if mask & PRINTMASK_NORMAL:
                    print("   Normal: {:+.3f} {:+.3f} {:+.3f}".format(v.normal.x, v.normal.y, v.normal.z) )
                if mask & PRINTMASK_UV:
                    print("        Uv: {:+.3f} {:+.3f}".format(v.uv[0], v.uv[1]) )
                if mask & PRINTMASK_TANGENT:
                    print("  Tangent: {:+.3f} {:+.3f} {:+.3f} {:+.3f}".format(v.tangent.x, v.tangent.y, v.tangent.z, v.tangent.w) )
                if mask & PRINTMASK_WEIGHT:
                    print("   Weights:", end='')
                    for w in v.weights:
                        print("  {:d} {:.3f}".format(w[0],w[1]), end='' )
                    print()
                #if iv > 20:
                #    break
        for iib,ib in enumerate(model.indexBuffers):
            print(" Index buffer {:d}".format(iib) )
            for iix,ix in enumerate(ib.indexes):
                if iix and (iix % 12) == 0:
                    print()
                if (iix % 3) == 0:
                    print("|", end='' )
                print(" {:3d}".format(ix), end='' )
            print()
        for ib, bone in enumerate(model.bones):
            print(" Bone {:d} {:s}".format(ib, bone.name) )
            print("   parent index: {:d}".format(bone.parentIndex) )
            print("       position: " +str(bone.position) )
            print("       rotation: " +str(bone.rotation) )
            print("          scale: " +str(bone.scale) )
            print("  collisionMask: " +str(bone.collisionMask) )
            print("         radius: " +str(bone.radius) )
            print("  inverseMatrix:\n" +str(bone.inverseMatrix) )
        for morph in model.morphs:
            print(" Morph {:s}".format(morph.name) )
            for ivb, vb in morph.vertexBufferMap.items():
                print("  Vertex buffer {:d}".format(ivb) )
                print("  Mask: 0x{:X}".format(vb.elementMask) )
                for iv,v in enumerate(vb.vertices):
                    print("  Vertex {:d}".format(iv) )
                    if mask & PRINTMASK_COORD:
                        print("    Coord: {:+.3f} {:+.3f} {:+.3f}".format(v.pos.x, v.pos.y, v.pos.z) )
                    if mask & PRINTMASK_NORMAL:
                        print("   Normal: {:+.3f} {:+.3f} {:+.3f}".format(v.normal.x, v.normal.y, v.normal.z) )
                    if mask & PRINTMASK_UV:
                        print("        Uv: {:+.3f} {:+.3f}".format(v.uv[0], v.uv[1]) )
                    if mask & PRINTMASK_TANGENT:
                        print("  Tangent: {:+.3f} {:+.3f} {:+.3f} {:+.3f}".format(v.tangent.x, v.tangent.y, v.tangent.z, v.tangent.w) )

    print()


def PrintVerts(mesh):        
    print("Mesh: " + mesh.name)
    print(" Vertices: ", len(mesh.vertices))
    for i, vt in enumerate(mesh.vertices):
        print("{:3d}  coords: ".format(vt.index) + str(vt.co))
        print("    normals: " +str(vt.normal))
        if i > 12: break

def PrintAll(tData):    
    print('Vertexes:')
    for i,v in enumerate(tData.verticesList):
        print(i)
        print(v)
        if i > 20:
            break

    print('\nMorphs:')
    for i,v in enumerate(tData.morphsList):
        print(i)
        print(v)

    print('\nMaterials:')
    for i,v in enumerate(tData.materialsList):
        print(i)
        print(v)

    print('\nGeometries:')
    for i,v in enumerate(tData.geometriesList):
        print(i)
        print(v)

    print('\nSkeleton:')
    for (k,v) in sorted(tData.bonesMap.items()):
        print(k)
        print(v)
                
def PrintMesh(mesh):        
    print("Mesh: " + mesh.name)
    print(" vertices: ", len(mesh.vertices))
    print(" faces: " + str(len(mesh.polygons)))
    for vt in mesh.vertices:
        print(" Vertex ", vt.index)
        print("  coords: " + str(vt.co))
        print("  normals: " +str(vt.normal))
    for i,fc in enumerate(mesh.polygons):
        print(" Polygon ", i)
        print("  normal: " +str(fc.normal))
        print("  indexes: ", end="")
        for v in fc.vertices:
            print(v, " ", end="")
        print()

    