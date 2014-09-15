#include "Graph.h"
#include <ShortestWaysDialog.h>
#include <GlobalSettings.h>

Graph::Graph(QObject *parent) :
    QObject(parent)
{
    distanceMatrixCache = nullptr;
    predecessorCache = nullptr;

    predecessorCacheSize = 0;
    distanceMatrixCacheSize = 0;
}

Vertex *Graph::addVertex(const QPointF &center)
{
    Vertex* newVertex = new Vertex(center);
    vertices.append(newVertex);

    // Очистка кэша, уведомление обьектов об измненениях
    clearCache();
    emit changed();
    return newVertex;
}

bool Graph::addEdge(Edge *edge)
{
    // не нульове ребро
    if ((edge == nullptr) || !edge->getStart() ||
            !edge->getEnd()) {
        return false;
    }
    if (edge->getStart() == edge->getEnd()) {
        return false;
    }

    // ще не існує у графі
    int startID = edge->getStart()->getID();
    Vertex *end = edge->getEnd();
    if (edges.contains(startID)) {
        for (Edge *exEdge : edges.values(startID)) {
            if (end == exEdge->getEnd()) {
                return false;
            }
        }
    }

    edges.insert(edge->getStart()->getID(), edge);

    if (!vertices.contains(edge->getStart()))
    {
        vertices.append(edge->getStart());
    }
    if (!vertices.contains(edge->getEnd()))
    {
        vertices.append(edge->getEnd());
    }

    // Очистка кэша, уведомление обьектов об измненениях
    clearCache();
    emit changed();
    return edge->getStart()->connectToEndOf(edge);
}

int Graph::vertexCount() const
{
    return vertices.count();
}

bool Graph::hasEdges() const
{
    return !edges.isEmpty();
}

bool Graph::removeVertex(Vertex *vertex)
{
    if (!vertices.contains(vertex)) {
        return false;
    }

    vertices.removeAll(vertex);
    vertex->isolate();
    delete vertex;
    return true;
}

int **Graph::distanceMatrix() const
{
    int n = vertexCount();      // размер матрицы
    if (n == 0) {
        return nullptr;
    }

    int **M = new int *[n];     // выделение памяти
    for (int i = 0; i < n; ++i) {
        M[i] = new int [n];
    }


    if (distanceMatrixCache == nullptr) {

        // Заполнение матрицы знаками отсутствия путей
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    M[i][j] = INT_MAX;
                } else {
                    M[i][j] = 0;    // Обнуление главной диагонали матрицы
                }
            }
        }

        // Осмотр прикрепленных вершин
        for (Edge *edge : edges) {
            int start = edge->getStart()->getID() - 1;
            int end = edge->getEnd()->getID() - 1;
            M[start][end] = edge->getVeigth();
        }

        // Выделение памяти для кэша
        distanceMatrixCache = new int *[n];
        for (int i = 0; i < n; ++i) {
            distanceMatrixCache[i] = new int [n];
        }

        // Инициализация кэша
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                distanceMatrixCache[i][j] = M[i][j];
            }
        }
    } else {

        // Копирование матрицы из кеша
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                M[i][j] = distanceMatrixCache[i][j];
            }
        }
    }

    return M;
}

int **Graph::shortestPathsByFloyd() const
{
    return negativeLoopCheck(shortestPathsByFloydWithoutNegativeLoopCheck());
}

int **Graph::shortestPathsByDantzig() {
    return negativeLoopCheck(shortestPathsByDantzigWithoutNegativeLoopCheck());
}

int *Graph::shortestPathsByBellmanFord(int fromIndex) const
{
    if (!vertexIndexCheck(fromIndex)) {
        return nullptr;
    }

    // Проверяем и подготавливаем кэш
    bool cacheExists = hasPredecessorCacheFor(fromIndex);
    if (!cacheExists) {
        preparePredecessorCacheFor(fromIndex);
    }

    // Данные для хранения динамических данных
    int *weight = new int[vertexCount()];   // масив кратчайших путей
    bool somethingChanged = true;           // флаг изменений в масиве

    // Инициализация
    for (int i = 0; i < vertexCount(); ++i) {
        weight[i] = ((i + 1) == fromIndex) ? 0 : INT_MAX;
    }

    // (V - 1) итераций для учета минимумов каждого ребра кроме текущего
    for (int i = 0; (i < vertexCount() - 1) && somethingChanged; ++i) {
        somethingChanged = false;

        // Обход ребер для поиска сокращений
        for (Edge *edge : edges) {
            int edgeWeight = edge->getVeigth();

            if (edgeWeight < INT_MAX) {
                int u = edge->getStart()->getID() - 1;
                int v = edge->getEnd()->getID() - 1;
                int newWeight = sum(weight[u], edge->getVeigth());
                if (newWeight < weight[v]) {
                    weight[v] = newWeight;
                    if (!cacheExists) {
                        predecessorCache[fromIndex - 1][v] = u + 1;
                    }
                    somethingChanged = true;
                }
            }
        }
    }

    // Лишняя итерация для проверки наличия отрицательных циклов
    for (Edge *edge : edges) {
        int edgeWeight = edge->getVeigth();

        if (edgeWeight < INT_MAX) {
            int u = edge->getStart()->getID() - 1;
            int v = edge->getEnd()->getID() - 1;
            int newWeight = sum(weight[u], edgeWeight);
            if (newWeight < weight[v]) {
                delete[] predecessorCache[fromIndex - 1];
                delete[] predecessorCache;
                predecessorCache = nullptr;
                return nullptr;
            }
        }
    }

    return weight;
}

int *Graph::shortestPathsByDijkstra(int fromIndex) const
{
    if (!vertexIndexCheck(fromIndex)) {
        return nullptr;
    }

    // Predecessor Vector
    bool cacheExists = hasPredecessorCacheFor(fromIndex);
    if (!cacheExists) {
        preparePredecessorCacheFor(fromIndex);
    }

    // shortest path matrix and vertices set
    int *weight = new int[vertexCount()];
    QMultiMap<int, Vertex*> set;
    for (int i = 0; i < vertexCount(); ++i) {
        if (i == (fromIndex - 1)) {
            set.insert(0, vertices.at(i));
            weight[i] = 0;
        } else {
            weight[i] = INT_MAX;
        }
    }

    // Маркеры пройденности вершины
    bool *passed = new bool[vertexCount()];
    for (int i = 0; i < vertexCount(); ++i) {
        passed[i] = false;
    }

    // Обход вершин графа
    while (!set.isEmpty()) {

        // наименьшая метка вершины
        int minWeight = set.firstKey();

        // при отсутсвии других связаных вершин прерываем поиск
        if (minWeight == INT_MAX) {
            break;
        }

        // вершина с найменшей меткой
        Vertex *u = set.take(minWeight); // текущая вершина
        int uID = u->getID() - 1;        // индекс текущей вершины
        passed[uID] = true;              // отметим пройденой

        // Обход вершин для поиска сокращений
        for (Edge *edge : *u->getOutgoingEdges()) {
            int edgeWeight = edge->getVeigth();

            // Отсеивает случаи недостижимых вершин
            if (edgeWeight < INT_MAX) {
                Vertex *v = edge->getEnd();      // вершина-сосед
                int vID = v->getID() - 1;
                int newWeight = sum(weight[uID], edgeWeight);

                // Релаксируем путь (u, v)
                if (newWeight < weight[vID]) {
                    weight[vID] = newWeight;
                    if (!cacheExists) {
                        predecessorCache[fromIndex - 1][vID] = uID + 1;
                    }

                    // В случае непосещенности добавляем
                    // новую вершину в множество
                    if (!passed[vID]) {
                        set.insert(weight[vID], v);
                    }
                }
            }
        }
    }

    return weight;
}

//int *Graph::renewShortestPaths(int from, int to) const {
//    if (predecessorCache == nullptr &&
//            predecessorCache[from] == nullptr) {
//        shortestPathsByBellmanFord(from);
//    }

//TODO

//    return nullptr;
//}

int **Graph::predecessorMatrix() const
{
    if (predecessorCache == nullptr) {
        shortestPathsByFloyd();
    }

    // copies vector from cache
    int **M = new int* [vertexCount()];
    for (int i = 0; i < vertexCount(); ++i) {
        M[i] = new int [vertexCount()];
        for (int j = 0; j < vertexCount(); ++j) {
            M[i][j] = predecessorCache[i][j];
        }
    }

    return M;
}

int *Graph::predecessorVector(int vertexIndex) const
{
    if (!vertexIndexCheck(vertexIndex)) {
        return nullptr;
    }

    return predecessorCache[vertexIndex - 1];
}

bool Graph::isPlanar() const
{
    int n = vertexCount();
    if (n < 5) {
        return true;
    }


    bool **M = new bool*[n];
    for (int i = 0; i < n; ++i) {
        M[i] = new bool[n];

        for (int j = 0; j < n; ++j) {
            M[i][j] = 0;
        }
    }

    for (Edge *e : edges) {
        int id1 = e->getStart()->getID() - 1;
        int id2 = e->getEnd()->getID() - 1;
        M[id1][id2] = 1;
        M[id2][id1] = 1;
    }




    // K33 - search
    for (int v1 = 0; v1 < n; ++v1) {
        for (int v2 = 0; v2 < n; ++v2) {
            if (!M[v1][v2] && (v1 != v2)) {
                for (int v3 = 0; v3 < n; ++v3) {
                    if (!M[v1][v3] && !M[v2][v3] &&
                            (v1 != v3) && (v2 != v3)) {

                        // До цього моменту знайдено 3 несуміжні вершини
                        for (int v4 = 0; v4 < n; ++v4) {
                            if (M[v1][v4] && M[v2][v4] && M[v3][v4]) {

                                // Вже знайдено v4, суміжну до всіх трьох
                                for (int v5 = 0; v5 < n; ++v5) {
                                    if (M[v1][v5] && M[v2][v5] &&
                                            M[v3][v5] && !M[v4][v5] &&
                                            (v4 != v5))
                                    {

                                        // Знайдено v5, суміжну для перших 3
                                        // перших 3 та не суміжну до 4
                                        for (int v6 = 0; v6 < n; ++v6) {
                                            if (M[v1][v6] && M[v2][v6] &&
                                                    M[v3][v6] && !M[v4][v6] &&
                                                    !M[v5][v6] && (v3 != v6) &&
                                                    (v4 != v6))
                                            {
                                                delete [] M;
                                                return false;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // K5 - search
    for (int v1 = 0; v1 < n; ++v1) {
        for (int v2 = 0; v2 < n; ++v2) {
            if (M[v1][v2]) {
                for (int v3 = 0; v3 < n; ++v3) {
                    if (M[v1][v3] && M[v2][v3]) {
                        for (int v4 = 0; v4 < n; ++v4) {
                            if (M[v1][v4] && M[v2][v4] && M[v3][v4]) {
                                for (int v5 = 0; v5 < n; ++v5) {
                                    if (M[v1][v5] && M[v2][v5] &&
                                            M[v3][v5] && M[v4][v5]) {
                                        // Знайдений повний граф K5
                                        delete[] M;
                                        return false;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return true;
}


QMap<int, int> Graph::colors() const
{
    QMap<int, int> iColors;
//    int iCount = 1;
    int n = vertexCount();
    for (int i = 0; i < n; i++)
    {
        iColors[i] = -1;
    }
    iColors[0] = 0;

    bool **ad = new bool*[n];
    for (int i = 0; i < n; ++i) {
        ad[i] = new bool[n];

        for (int j = 0; j < n; ++j) {
            ad[i][j] = 0;
        }
    }

    for (Edge *e : edges) {
        int id1 = e->getStart()->getID() - 1;
        int id2 = e->getEnd()->getID() - 1;
        ad[id1][id2] = 1;
        ad[id2][id1] = 1;
    }

    for (int i = 0; i < n; i++)	//Main vert
    {
        int tmpCol = 0;

        bool b = false;
        do{
            b = true;
            iColors[i] = tmpCol;
            for (int j = 0; j < n; j++) {
                if(i == j) continue;
                if ((ad[i][j] == 1 || ad[j][i] == 1) && iColors[j] == tmpCol) {
                    b = false;
                    tmpCol++;
                    j = n;
                }
            }
        } while (b != true);
        iColors[i] = tmpCol;
    }
    delete ad;
    return iColors;
//    int max = iColors.value(iColors.keys().at(0));
//    for(int n : iColors.values()) {
//        if(n > max) {
//            max = n;
//        }
//    }
//    return max + 1;
}

int **Graph::shortestPathsByFloydWithoutNegativeLoopCheck() const
{
    // подготовка кэша для записи
    bool predecessorRefreshNeeded = predecessorCache == nullptr;
    if (predecessorRefreshNeeded) {
        preparePredecessorCache();
    }

    int n = vertexCount();      // количество вершин в графе
    int **D = distanceMatrix(); // начальная матрица расстояний

    // Цикл перебора путей через первых k вершин
    for (int k = 0; k < n; ++k) {       // Обновление матрицы для каждого значения k
        for (int i = 0; i < n; ++i) {
            if (D[i][k] < INT_MAX) {
                for (int j = 0; j < n; ++j) {
                    if (D[k][j] < INT_MAX) {
                        int newWeight = sum(D[i][k], D[k][j]); // новый вес

                        if (D[i][j] > newWeight) {
                            D[i][j] = newWeight;
                            if (predecessorRefreshNeeded) {
                                predecessorCache[i][j] = predecessorCache[k][j];
                            }
                        }
                    }
                }
            }
        }
    }
    return D;
}



int **Graph::shortestPathsByDantzigWithoutNegativeLoopCheck() const
{
    // подготовка кэша в случае надобности для записи
    if (!hasPredecessorCache()) {
        preparePredecessorCache();
    }

    int n = vertexCount();      // количество вершин в графе
    int **D = distanceMatrix(); // начальная матрица расстояний

    // У циклі поступово збільшуємо порядок нових матриць
    for (int m = 0; m < n; ++m) {

        // оновлюємо значення у новій матриці порядку m
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j) {

                // Заповнення нового рядку m. Перебирання кожної
                // з вершин попередньої матриці як проміжної
                relaxPath(m, j, i, D);

                // Заповнення нового стовпця. Перебирання кожної з
                // вершин попередньої матриці як проміжної
                relaxPath(i, j, m, D);

                // Релаксування старої матриці, базуючись на даних
                // нового стовпця та рядку
                relaxPath(i, m, j, D);
            }
        }
    }

    // повертаємо матрицю найкоротших відстаней
    return D;
}

    // Поступово збільшуємо порядок нових матриць
//    for (int m = 0; m < n; ++m) {

//        // Заповнення нового рядку m
//        for (int j = 0; j < m; ++j) {

//            // Перебирання кожної з вершин попередньої матриці як проміжної
//            for (int i = 0; i < m; ++i) {
//                int newPath = sum(D[m][i], D[i][j]);    // Вага нового шляху

//                // Перевіримо, чи коротший новий шлях за поточний
//                if (newPath < D[m][j]) {

//                    // Якщо так, то запишему його як новий шлях
//                    D[m][j] = newPath;

//                    // Обновлюємо матрицю зворотніх відстаней
//                    if (!hasPredecessorCache()) {
//                        predecessorCache[m][i] = predecessorCache[i][j];
//                    }
//                }
//            }
//        }



//        // Заповнення нового стовпця m
//        for (int i = 0; i < m; ++i) {

//            // Перебирання кожної з вершин попередньої матриці як проміжної
//            for (int j = 0; j < m; ++j) {
//                int newPath = sum(D[i][j], D[j][m]);    // Вага нового шляху

//                // Перевіримо, чи коротший новий шлях за поточний
//                if (newPath < D[i][m]) {

//                    // Якщо так, то запишему його як новий шлях
//                    D[i][m] = newPath;

//                    // Обновлюємо матрицю зворотніх відстаней
//                    if (!hasPredecessorCache()) {
//                        predecessorCache[i][m] = predecessorCache[j][m];
//                    }
//                }
//            }
//        }

//        // Осматриваем матрицу D(m - 1)
//        for (int i = 0; i < m; ++i) {

//            // Якщо один із елементів суми - нескінченність, то сума не
//            // може впливати на найкоротші шляхи
//            if (D[i][m] < INT_MAX) {
//                for (int j = 0; j < m; ++j) {

//                    // Якщо один із елементів суми - нескінченність, то сума не
//                    // може впливати на найкоротші шляхи
//                    if (D[m][j] < INT_MAX) {
//                        D[i][j] = min(D[i][j], sum(D[i][m], D[m][j]));
//                        if (!hasPredecessorCache()) {
//                            predecessorCache[i][j] = predecessorCache[m][j];
//                        }
//                    }
//                }
//            }
//        }
//    }

//    return D;
//}

int **Graph::negativeLoopCheck(int **shortestPathsMatrix) const
{
    int n = vertexCount();
    int **D = shortestPathsMatrix;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {

                // Если путь от i до j через вершину k существует, и k лежит в
                // отрицательном цикле, то путь i -> j проходит через этот цикл
                if ((D[i][k] < INT_MAX) && (D[k][j] < INT_MAX) && (D[k][k] < 0 )) {
                    D[i][j] = INT_MIN;
                }
            }
        }
    }
    return D;
}

bool Graph::vertexIndexCheck(int index) const
{
    return (0 < index) && (index <= vertexCount());
}

// ПРИМИТИВНЫЕ МЕТОДЫ ДЛЯ РОБОТЫ АЛГОРИТМОВ

int Graph::min(int operand1, int operand2)
{
    return (operand1 > operand2) ? operand2 : operand1;
}

int Graph::sum(int operand1, int operand2)
{
    /* Отсеивание переполнений значениями бесконечности */
    if ((operand1 > 0) && (operand2 > 0) && (INT_MAX - operand2 < operand1)) {
        return INT_MAX;
    }

    if ((operand1 < 0) && (operand2 < 0) && (INT_MIN - operand2 > operand1)) {
        return INT_MIN;
    }

    return operand1 + operand2;
}

void Graph::preparePredecessorCache() const
{
    // Очищение старого кэша
    clearPredecessorCache();

    // Инициализация матрицы
    predecessorCacheSize = vertexCount();
    predecessorCache = new int* [predecessorCacheSize];
    for (int i = 0; i < predecessorCacheSize; ++i) {
        predecessorCache[i] = new int [predecessorCacheSize];
        for (int j = 0; j < predecessorCacheSize; ++j) {
            predecessorCache[i][j] = i + 1;
        }
        predecessorCache[i][i] = 0;
    }
}

void Graph::relaxPath(int from, int through, int to, int **D) const
{
    // Якщо шлях через проміжну вершину існує
    if (D[from][through] != INT_MAX &&
            D[through][to] != INT_MAX) {

        // вага шляху через проміжну вершину
        int newWeight = sum(D[from][through], D[through][to]);

        // Якщо нова вага менша за стару
        if (newWeight < D[from][to]) {

            // оновлюємо нову матрицю найкоротших відстаней
            D[from][to] = newWeight;

            // Оновлюємо матрицю відновлення
            if (!hasPredecessorCache()) {
                predecessorCache[from][to] = predecessorCache[through][to];
            }
        }
    }
}

void Graph::clearPredecessorCache() const
{
    // Завершаем выполнение в случае чистого кэша
    if (predecessorCache != nullptr) {
        for (int i = 0; i < predecessorCacheSize; ++i) {
            if (predecessorCache[i] != nullptr) {
                delete[] predecessorCache[i];
            }
        }
        delete[] predecessorCache;
        predecessorCache = nullptr;
        predecessorCacheSize = 0;
    }
}

void Graph::clearCache() const
{
    // Завершаем выполнение в случае чистого кэша
    if (distanceMatrixCache != nullptr) {
        for (int i = 0; i < distanceMatrixCacheSize; ++i) {
            if (distanceMatrixCache[i] != nullptr) {
                delete[] distanceMatrixCache[i];
            }
        }
        delete[] distanceMatrixCache;
        distanceMatrixCache = nullptr;
        distanceMatrixCacheSize = 0;
    }
    clearPredecessorCache();
}

void Graph::preparePredecessorCacheFor(int index) const
{
    int i = index - 1;

    // Очищение старого кэша
    clearPredecessorCache();

    // Инициализация матрицы
    predecessorCacheSize = 1;
    predecessorCache = new int* [vertexCount()];
    predecessorCache[i] = new int [vertexCount()];
    for (int j = 0; j < vertexCount(); ++j) {
        if (j == i) {
            predecessorCache[i][i] = 0;
        } else {
            predecessorCache[i][j] = index;
            predecessorCache[j] = nullptr;
        }
    }
}

bool Graph::hasPredecessorCache() const
{
    return predecessorCache != nullptr;
}

bool Graph::hasPredecessorCacheFor(int index) const
{
    return predecessorCache != nullptr &&
            predecessorCache[index - 1] != nullptr;
}


void Graph::shortestWaysWindow()
{
    ShortestWaysDialog a (this);
    a.exec();

}

void Graph::newEdgesVeight(int value)
{
    GlobalSettings::setEdgeVeight(value);
}
