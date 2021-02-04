#include <iostream>
#include <vector>

using namespace std;

template <class N, class E> class Edge;

template <class N>class NodeAlreadyExists;

template <class N> class NodeDoesNotExist;

template <class N> class EdgeAlreadyExists;

template <class N> class EdgeDoesNotExist;

template <class N, class E>
class Node {
public:
    N info;
    vector< Edge<N,E> > edges;
    Node(N inf) {
        info = inf;
    }
};

template <class N, class E>
class Edge {
public:
    E value;
    Node<N,E> *destination;
    Edge(Node<N,E> *dest, E val) {
        value = val;
        destination = dest;
    }
};

template <class N, class E>
class Graph {
    vector< Node<N,E> *> nodes;
public:
    Graph() {
    }
    ~Graph() {
        for (Node<N,E> *nd : nodes)
            delete nd;
    }
    Graph & addNode(const N &inf) {
        for (Node<N,E> *nd : nodes)
            if (nd->info == inf)
                throw NodeAlreadyExists<N>(inf);
        nodes.push_back(new Node<N,E>(inf));
        return *this;
    }
    Graph & addEdge(const N &begin, const N &end, const E &val) {
        Node<N,E> *rem = NULL;
        Node<N,E> *dest = NULL;
        for (Node<N,E> *nd : nodes) {
            if (nd->info == begin)
                rem = nd;
            if (nd->info == end)
                dest = nd;
            if (rem != NULL && dest != NULL)
                break;
        }
        if (rem == NULL)
            throw NodeDoesNotExist<N>(begin);
        else if (dest == NULL)
            throw NodeDoesNotExist<N>(end);
        for (Edge<N,E> &ed : rem->edges)
            if (ed.destination == dest)
                throw EdgeAlreadyExists<N>(begin, end);
        rem->edges.push_back(Edge<N,E>(dest, val));
        return *this;
    }
    Graph & removeEdge(const N &begin, const N &end) {
        Node<N,E> *rem = NULL;
        Node<N,E> *dest = NULL;
        for (Node<N,E> *nd : nodes) {
            if (nd->info == begin)
                rem = nd;
            if (nd->info == end)
                dest = nd;
            if (rem != NULL && dest != NULL)
                break;
        }
        if (rem == NULL)
            throw NodeDoesNotExist<N>(begin);
        else if (dest == NULL)
            throw NodeDoesNotExist<N>(end);
        for (auto it=rem->edges.begin(); it != rem->edges.end(); ++it)
            if (it->destination == dest) {
                rem->edges.erase(it);
                return *this;
            }
        throw EdgeDoesNotExist<N>(rem->info, dest->info);
    }
    E & edgeValue(const N &begin, const N &end) {
        Node<N,E> *rem = NULL;
        Node<N,E> *dest = NULL;
        for (Node<N,E> *nd : nodes) {
            if (nd->info == begin)
                rem = nd;
            if (nd->info == end)
                dest = nd;
            if (rem != NULL && dest != NULL)
                break;
        }
        if (rem == NULL)
            throw NodeDoesNotExist<N>(begin);
        else if (dest == NULL)
            throw NodeDoesNotExist<N>(end);
        for (Edge<N,E> &ed : rem->edges)
            if (ed.destination == dest)
                return ed.value;
        throw EdgeDoesNotExist<N>(rem->info, dest->info);
    }
    unsigned numEdges(void) const {
        unsigned counter = 0;
        for (Node<N,E> *nd : nodes)
            counter += nd->edges.size();
        return counter;
    }
    unsigned numNodes(void) const {
        return nodes.size();
    }
    void print(std::ostream &os) const {
        for (Node<N,E> *nd : nodes) {
            os << "( " << nd->info << " ";
            for (Edge<N,E> &ed : nd->edges)
                os << "[" << ed.destination->info << " " << ed.value << "] ";
            os << ") ";
        }
    }
};

template <class N, class E>
std::ostream & operator<<(std::ostream &out, const Graph<N,E> &g) {
    g.print(out);
    return out;
}


// exception NodeAlreadyExists
template <class N>
class NodeAlreadyExists
{
public:
    N info;
    NodeAlreadyExists(N inf) { info=inf; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NodeAlreadyExists<N> &no)
{ out << "Node already exists: " << no.info; return out; }


// exception NodeDoesNotExist
template <class N>
class NodeDoesNotExist {
public:
    N info;
    NodeDoesNotExist(N inf) {
        info = inf;
    }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NodeDoesNotExist<N> &no)
{ out << "Node does not exist: " << no.info; return out; }


// exception EdgeAlreadyExists
template <class N>
class EdgeAlreadyExists
{
public:
    N node1, node2;
    EdgeAlreadyExists(N nd1, N nd2) { node1=nd1; node2=nd2; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const EdgeAlreadyExists<N> &no)
{ out << "Edge already exists: " << no.node1 << " , " << no.node2; return out; }


// exception EdgeDoesNotExist
template <class N>
class EdgeDoesNotExist
{
public:
    N node1, node2;
    EdgeDoesNotExist(N nd1, N nd2) { node1=nd1; node2=nd2; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const EdgeDoesNotExist<N> &no)
{ out << "Edge does not exist: " << no.node1 << " , " << no.node2; return out; }

