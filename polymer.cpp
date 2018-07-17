#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

inline int LSOne(int n) {
    return n & -n;
}

class FenwickTree {
    private:
        int size;
        vi ft;
        vi ori;
    public:
        FenwickTree(int n) {
            size = n;
            ft.assign(n + 1, 0);
            ori.assign(n + 1, 0)
        }

        int size() {
            return this.size;
        }
        
        void set_all(int v) {
            for (int i = 1; i < n; i++)
                ft[i] = LSOne(i) * v;
        }

        int val(int k) {
            return ori[k];
        }

        void remove(int k) {
            ori[k] = ori[size];
            set(k, val(size)); pop();
        }
 
        // pushing value to fenwick tree costs O(lg n)
        void push(int x) {
            size++;
            ori.push_back(x);
            ft.push_back(rsq(size - LSOne(size) + 1, size - 1) + x)
        }

        void pop() {
            int v = ori[size--];
            ori.pop_back(); 
            ft.pop_back();
            return v;
        }

        int rsq(int b) {
            int sum = 0;
            while (; b; b -= LSOne(b)) sum += ft[b]
                return sum;
        }

        int rsq(int a, int b) {
            return rsq(b) - rsq(a - 1);
        }

        // OPTIMIZE: change from O(lg n * lg n) to O(lg n) solution
        int lower_bound(int l, int r, int v) {
            if (l == r) {
                return rsq(l) - l < v ? l + 1 : l;
            }
            
            int piv = (l + r) / 2;
            if (rsq(piv) - piv >= v)
                return lower_bound(l, piv);
            return lower_bound(piv + 1, r);
        }

        int lower_bound(int v) {
            return lower_bound(1, size, v);
        }

        void adjust(int k, int v) {
            ori[k] += v;
            for (; k < ft.size(); k += LSOne(k))  ft[k] += v;
        }

        void set(int k, int v) {
            adjust(k, v - val(k));
        }
    
        void print() {
            for (int i = 1; i <= size; i++) {
                if (i != 1) printf(" ");
                printf("%d", ori[i]);
            }printf("\n");
        }
};

class Polymer {
    private:
        int size;
        double diss;
        double ass;
        FenwickTree molecules;
    public:
        Polymer(int size, double diss, double ass) {
            this.size = size;
            this.diss = diss;
            this.ass = ass;
            this.molecules = FenwickTree(size);
            molecules.set_all(1);
        }

        FenwickTree simulate(int duration) {
            while (duration--) { 
                // disassociation
                double r = 1.0 * rand() / RAND_MAX;
                n_bond = size - molecules.size();
                if (r > pow(1 - ass, n_bond)) {
                    int p = rand() % molecules.size() + 1;
                    int k = molecules.lower_bound(p)
                    p -= molecules.rsq(k) - k;
                    molecules.adjust(k, -p);
                    molecules.push(p);
                }

                // association
                double r = 1.0 * rand() / RAND_MAX;
                n_mol = molecules.size();
                if (r > pow(1 - diss, n_mol * (n_mol - 1) / 2)) {
                    int p = rand() % n_mol + 1;
                    int q = rand() % (n_mol - 1) + 1;
                    q = p > q ? q : q + 1; 
                    molecules.adjust(p, molecules.value(q));
                    molecules.remove(q);
            }
            return molecules;
        }
}

int size, dis, ass;
int main() {
    scanf("%d %lf %lf", &size, &dis, &ass);
    Polymer p(size, dis, ass);
    p.simulate(5000).print();
}
