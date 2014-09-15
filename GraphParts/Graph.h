#ifndef GRAPH_H
#define GRAPH_H

#include <QList>
#include <QMultiHash>
#include "Vertex.h"
#include "Edge.h"

class Graph : public QObject
{
    Q_OBJECT // маркер того, что класс может иметь сигналы и слоты

    QList<Vertex*>           vertices;    // вершины графа
    QMultiHash<int, Edge*>   edges;       // ребра графа

    mutable int **distanceMatrixCache;   // кеширует матрицу расстояний
    mutable int distanceMatrixCacheSize; // кеширует размер матрицы расстояний
    mutable int **predecessorCache;      // кеширует матрицу вершин предшественников
    mutable int predecessorCacheSize;    // кеширует размер матрицы предшественников

public:

    /**
     * Конструктор класса по умолчанию
     * @brief Graph
     * @param parent - обьект родителя
     */
    explicit Graph(QObject *parent = 0);

    /**
     * Добавить указаное ребро в граф. Возвращает
     * false если по каким-то причинам не удалось добавить
     * ребро (ребро не имеет начала, конца или уже есть
     * в графе), true - в другом случае.
     *
     * @brief addEdge
     * @param edge - ребро  для добавления в граф
     * @return было ли добавлено ребро
     */
    Vertex *addVertex(const QPointF &center);

    /**
     * Добавить указаное ребро в граф. Возвращает
     * false если по каким-то причинам не удалось добавить
     * ребро (ребро не имеет начала, конца или уже есть
     * в графе), true - в другом случае.
     *
     * @brief addEdge
     * @param edge - ребро  для добавления в граф
     * @return было ли добавлено ребро
     */
    bool addEdge(Edge *edge);

    /**
     * Возвращает количество вершин в графе.
     *
     * @brief vertexCount
     * @return количество вершин в графе
     */
    int vertexCount() const;

    /**
     * Проверяет наличие ребер в графе.
     * Возвращает true, если граф содержит ребра,
     * false в случае их отсутствия.
     *
     * @brief hasEdges
     * @return true если граф содержит ребра,
     * false в случае их отсутствия.
     */
    bool hasEdges() const;

    /**
     * @brief removeVertex
     *
     * Удаляет вершину из графа. Возвращает true,
     * если вершина была найдена и удалена,
     * false - если вершина не была найдена в графе.
     *
     * @param vertex вершина для удаления
     * @return true, если вершина была найдена и удалена,
     * false, если вершина  не была найдена в графе.
     */
    bool removeVertex(Vertex *vertex);

    // МЕТОДЫ КРАТЧАЙШИХ РАССТОЯНИЙ

    /**
     *  Возвращает матрицу расстояний графа, которая включает
     * веса всех дуг графа. При отсутсвии отрицательных петель
     * главная диагональ заполнена нолями. Матрица кэшируеться,
     * для быстрого доступа для других методов.
     *  Матрица используеться алгоритмами для поиска кратчайших
     * путей среди всех вершин, такими как Флойда-Уоршелла,
     * Данцига.
     *
     *
     * @brief Graph::distanceMatrix
     * @return матрицу расстояний графа.
     */
    int **distanceMatrix() const;

    /**
     * Поиск кратчайших путей по алгоритму Флойда-Уоршелла.
     * Алгоритм усовершенствованный для поиска кратчайших путей
     * даже при наличии отрицательных циклов.
     *
     * @brief Graph::shortestPathsByFloyd
     * @return матрицу кратчайших путей (без учета циклов с отрицательными весами)
     */
    int **shortestPathsByFloyd() const;

    /**
     * Поиск кратчайших путей по алгоритму Данцига.
     * Алгоритм усовершенствованный для поиска кратчайших путей
     * даже при наличии отрицательных циклов.
     *
     * @brief Graph::shortestPathsByDantzig
     * @return матрицу кратчайших путей (без учета циклов с отрицательными весами)
     */
    int **shortestPathsByDantzig();

    /**
     * Алгоритм Дейстры для поиска кратчайших путей
     * исходящих из одного источника (вершины) с
     * индексом fromIndex. Для оптимизации обхода ребер
     * используется хэш-таблица. Алгоритм работает
     * только для неотрицательных весов ребер.
     * Возвращает вектор кратчайших расстояний из
     * вершины с индексом fromIndex до всех вершин графа.
     *
     * @brief Graph::shortestPathsByDijkstra
     * @param fromIndex индекс стартовой вершины
     * @return Вектор кратчайших расстояний из
     * вершины с индексом fromIndex до всех вершин графа.
     */
    int *shortestPathsByDijkstra(int fromIndex) const;
    int *shortestPathsByBellmanFord(int fromIndex) const;

    // МЕТОДЫ ВОССТАНОВЛЕНИЯ ПУТИ

    //int *renewShortestPaths(int from, int to) const;
    int **predecessorMatrix() const;
    int *predecessorVector(int vertexIndex) const;

    bool isPlanar() const;
    QMap<int, int> colors() const;

private:

    // НЕПОЛНЫЕ ВЕРСИИ АЛГОРИТМОВ КРАТЧАЙШЕГО ПУТИ

    /**
     * Поиск кратчайших путей по алгоритму Флойда-Уоршелла.
     * Не работает для циклов с отрицательными весами
     *
     * @brief Graph::shortestPathsByFloydWithoutNegativeLoopCheck
     * @return матрицу кратчайших путей (без учета циклов с отрицательными весами)
     */
    int **shortestPathsByFloydWithoutNegativeLoopCheck() const;
    int **shortestPathsByDantzigWithoutNegativeLoopCheck() const;

    // МЕТОДЫ ДЛЯ ПРОВЕРКИ ДАННЫХ

    /**
     * @brief negativeLoopCheck
     *
     * Осматривает матрицу кратчайших растояний, например,
     * полученую в результате роботы алгоритма Флойда-Уоршелла
     * или Данцига и проводит обработку встреченных негативных
     * циклов. Возвращает обработаную матрицу кратчайших
     * расстояний, которая учитывает негативные циклы.
     *
     * @param shortestPathsMatrix
     * @return обработаную матрицу кратчайших
     * расстояний, которая учитывает негативные циклы.
     */
    int **negativeLoopCheck(int **shortestPathsMatrix) const;

    /**
     * @brief vertexIndexCheck
     *
     * Проверяет наличие в графе вершины с индексом index.
     * Возвращает true если такая есть, иначе - false.
     *
     * @param index
     * @return true при наличии в графе вершины с индексом index,
     * иначе - false.
     */
    bool vertexIndexCheck(int index) const;

    // ПРИМИТИВНЫЕ МЕТОДЫ ДЛЯ РОБОТЫ АЛГОРИТМОВ

    static int min(int operand1, int operand2);
    static int sum(int operand1, int operand2);

    /**
     * @brief preparePredecessorCache
     *
     * Подгатавливает кэш матрицы предыдущих
     * вершин графа для записи новых значений.
     */
    void preparePredecessorCache() const;

    /**
     * @brief relaxPath
     *
     * Намагається релаксувати шлях у матриці з from до to, спробою
     * прокласти шлях через вершину through. Тобто, якщо сума шляхів
     * з from до through та з through до to менша за поточний
     * шлях з from до to, то замінюємо останній на цю суму.
     * В результаті замінює елемент матриці, що відповідає
     * відстані, яку релаксує функція.
     *
     * @param from - вершина, звідки прокладається відстань у графі
     * @param through - вершина, через яку, можливо, проходитиме новий шлях
     * @param to - вершина, до якої прокладається шлях
     * @param D - матриця відстаней графу, що розглядається
     * @param P - матриця відновлення шляхів у графі
     */
    void relaxPath(int from, int through, int to, int **D) const;

    /**
     * @brief clearPredecessorCache
     *
     * Очищает кэш матрицы предыдущих вершин
     * графа.
     */
    void clearPredecessorCache() const;

    /**
     * @brief clearPredecessorCache
     *
     * Очищает весь кэш, хранящийся в этом экземпляре
     * графа. В кэш входят: матрицы предыдущих вершин
     * и расстояний.
     */
    void clearCache() const;

    /**
     * @brief preparePredecessorCache
     *
     * Подгатавливает кэш вектора предыдущих
     * вершин графа для записи новых значений
     * для вершины с индексом index.
     *
     * @param index - индекс вершины для записи
     * предыдущих вершин
     */
    void preparePredecessorCacheFor(int index) const;

    bool hasPredecessorCache() const;

    bool hasPredecessorCacheFor(int index) const;    

signals:
    void changed();
public slots:
    void shortestWaysWindow();
    void newEdgesVeight(int value);
};

#endif // GRAPH_H
