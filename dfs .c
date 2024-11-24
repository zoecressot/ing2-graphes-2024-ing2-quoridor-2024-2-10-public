#include "graphe1.h"

// Creer un graphe avec numVertices sommets
Graphe* creerGraphe(int numVertices) {
    Graphe* graphe = (Graphe*)malloc(sizeof(Graphe));
    graphe->numVertices = numVertices;

    graphe->adjMatrix = (int**)malloc(numVertices * sizeof(int*));
    for (int i = 0; i < numVertices; i++) {
        graphe->adjMatrix[i] = (int*)malloc(numVertices * sizeof(int));
        for (int j = 0; j < numVertices; j++) {
            graphe->adjMatrix[i][j] = INT_MAX; // Pas de connexion initiale
        }
    }

    graphe->visited = (bool*)calloc(numVertices, sizeof(bool));

    return graphe;
}

// Ajouter une arete avec un poids entre src et dest
void ajouterArete(Graphe* graphe, int src, int dest, int poids) {
    graphe->adjMatrix[src][dest] = poids;
    graphe->adjMatrix[dest][src] = poids; // Pour un graphe non oriente
}

// Liberer la memoire du graphe
void libererGraphe(Graphe* graphe) {
    for (int i = 0; i < graphe->numVertices; i++) {
        free(graphe->adjMatrix[i]);
    }
    free(graphe->adjMatrix);
    free(graphe->visited);
    free(graphe);
}

// Algorithme DFS
void dfs(Graphe* graphe, int startVertex, int* predecesseurs, int* distances, int* chemin, int* cheminIndex) {
    graphe->visited[startVertex] = true;
    chemin[(*cheminIndex)++] = startVertex; // Ajouter le sommet au chemin

    for (int i = 0; i < graphe->numVertices; i++) {
        if (graphe->adjMatrix[startVertex][i] != INT_MAX && !graphe->visited[i]) {
            int nouveauPoids = distances[startVertex] + graphe->adjMatrix[startVertex][i];
            if (nouveauPoids < distances[i]) {
                distances[i] = nouveauPoids;
                predecesseurs[i] = startVertex;
            }
            dfs(graphe, i, predecesseurs, distances, chemin, cheminIndex);
        }
    }
}
