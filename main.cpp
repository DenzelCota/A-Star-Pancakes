#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Estado {
    std::string panqueques;
    int costeMovimiento;
    int estimacion;
    int costeTotal;
    Estado(std::string panqueques, int costeMovimiento, int estimacion) : panqueques(panqueques), costeMovimiento(costeMovimiento), estimacion(estimacion), costeTotal(costeMovimiento + estimacion) {}
};

struct CompararEstado {
    bool operator()(const Estado& s1, const Estado& s2) const {
        return s1.costeTotal > s2.costeTotal;
    }
};

void invertirSubcadena(std::string& cadena, int indice) {
    std::reverse(cadena.begin(), cadena.begin() + indice + 1);
}

int heuristica(const std::string& actual, const std::string& final) {
    int contador = 0;
    for (int i = 0; i < actual.size(); ++i) {
        if (actual[i] != final[i]) {
            ++contador;
        }
    }
    return contador;
}

std::string aEstrella(std::string inicio, std::string final, int& contador) {
    std::priority_queue<Estado, std::vector<Estado>, CompararEstado> cola;
    std::unordered_map<std::string, int> puntuacionMovimiento;
    cola.emplace(inicio, 0, heuristica(inicio, final));
    puntuacionMovimiento[inicio] = 0;
    contador = 0;

    while (!cola.empty()) {
        Estado actual = cola.top();
        cola.pop();
        ++contador;

        if (actual.panqueques == final) {
            return actual.panqueques;
        }

        for (int i = 1; i < actual.panqueques.size(); ++i) {
            std::string siguiente = actual.panqueques;
            invertirSubcadena(siguiente, i);
            int nuevoCosteMovimiento = actual.costeMovimiento + 1;
            if (puntuacionMovimiento.find(siguiente) == puntuacionMovimiento.end() || nuevoCosteMovimiento < puntuacionMovimiento[siguiente]) {
                puntuacionMovimiento[siguiente] = nuevoCosteMovimiento;
                int nuevaEstimacion = heuristica(siguiente, final);
                Estado siguienteEstado(siguiente, nuevoCosteMovimiento, nuevaEstimacion);
                cola.push(siguienteEstado);
            }
        }
    }

    return "";
}

int main() {
    int longitudCadena;
    std::cout << "Introduce la longitud de la cadena a ordenar (maximo 26): ";
    std::cin >> longitudCadena;

    std::string panqueques = "abcdefghijklmnopqrstuvwxyz";
    panqueques = panqueques.substr(0, longitudCadena);
    std::string panquequesOrdenados = panqueques;

    std::cout << "Panqueques: " << panqueques << std::endl;
    std::random_shuffle(panqueques.begin(), panqueques.end());
    std::cout << "Panqueques desordenados: " << panqueques << std::endl;

    int contador = 0;

        std::string resultado = aEstrella(panqueques, panquequesOrdenados, contador);

    std::cout << "Panqueques ordenados: " << panquequesOrdenados << std::endl;

    if (resultado != "") {
        std::cout << "Panqueques resueltos: " << resultado << std::endl;
    } else {
        std::cout << "No se encontró una solución" << std::endl;
    }

    std::cout << "Nodos visitados: " << contador << std::endl;

    return 0;
}





