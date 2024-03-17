
import os
import _pickle as cPickle
from PIL import Image

class Piece:
    def __init__(self, n, s, e, w, c, name):
        # Save colors
        self.n = n
        self.s = s
        self.e = e
        self.w = w
        self.c = c

        self.name = name

        self.nc = None
        self.sc = None
        self.ec = None
        self.wc = None



# -----------
# GET PATCHES
    
# Check if serialized patch data is available
pieces = []
if os.path.isfile("patches.p"):
    print("Loading existing patch data pickle file")
    pieces = cPickle.load(open("patches.p", "rb"))
    
else:
    for file in os.listdir("patches"):
        im = Image.open("patches/" + file)
        pix = im.load()

        pieces.append(Piece(pix[1, 0], pix[1, 2], pix[2, 1], pix[0, 1], pix[1, 1], file))

    cPickle.dump(pieces, open("patches.p", "wb"))



# ------------
# SOLVE JIGSAW


if os.path.isfile("connected_patches.p"):
    pieces = cPickle.load(pieces, open("connected-patches.p", "rb"))
else:
    missingN = pieces
    missingS = pieces
    missingE = pieces
    missingW = pieces

    print(len(missingN))
    print(len(missingS))

    while len(missingN) > 0:
        n = missingN[-1]
        for j in range(len(missingS)):
            s = missingS[j]
            if n.n == s.s:
                n.nc = s
                s.sc = n
                missingN.pop()
                missingS.pop(j)
                print(len(missingN))
                print(len(missingS))
                break
        else:
            print("Couldn't find a match!")
            missingN.pop()

    print(len(missingN))
    print(len(missingS))
    

    cPickle.dump(pieces, open("connected_patches.p", "wb"))


invalidPieces = []
for p in pieces:
    count = 0
    if p.nc == None:
        count += 1
    if p.sc == None:
        count += 1
    if p.ec == None:
        count += 1
    if p.wc == None:
        count += 1

    if count > 2:
        invalidPieces.append(p)

print(len(pieces))
print(len(invalidPieces))


