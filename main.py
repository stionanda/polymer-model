from random import random as rand
from math import floor


def randint(a, b):
    return floor(rand() * (b - a)) + a


class PolymerModel():
    """docstring for PolymerModel"""
    def __init__(self, s, da_p, as_p):
        self.size = s
        self.molecules = [1] * s
        self.da_prob = da_p
        self.as_prob = as_p

    def mol_count(self):
        return len(self.molecules)

    def bond_count(self):
        return self.size - self.mol_count()

    def simulate(self, duration):
        for p in range(duration):
            molecules = self.molecules
            mc = self.mol_count()
            new_mol = []
            for i in range(mc):
                count = 1
                for j in range(1, molecules[i]):
                    if rand() < self.da_prob:
                        new_mol += [count]
                        count = 0
                    count += 1
                new_mol += [count]

            self.molecules = new_mol
            molecules = self.molecules

            mc = self.mol_count()
            if rand() > (1 - self.as_prob) ** ((mc * mc - 1) / 2):
                p = randint(0, mc)
                q = randint(1, mc)
                molecules[0], molecules[p] = molecules[p], molecules[0]
                molecules[q], molecules[mc - 1] = molecules[mc - 1], molecules[q]
                molecules[0] += molecules.pop()
        return molecules


def main():
    model = PolymerModel(1000, 0.00005, 0.00007)
    print(sorted(model.simulate(50000)))


if __name__ == '__main__':
    main()

