#include <iostream>
#include "console.h"
#include "basicgraph.h"
#include "simpio.h"
#include "set.h"
#include "priorityqueue.h"
#include "gwindow.h"
#include "gobjects.h"
#include "random.h"
#include "map.h"
#include <cmath>

using namespace std;

const bool GRID_GRAPH = true;

void kruskal(BasicGraph &graph, BasicGraph &mst);
void drawGraph(GWindow &gw, BasicGraph &graph, string title);
void adjustWindows(GWindow &gw1,GWindow &gw2);
void populateGraph(BasicGraph &graph,bool randomVerts = false);

int main() {
    // create two windows and stack them horizontally
    GWindow gwOrig,gwMst;

    // adjust the windows to make them look nice
    adjustWindows(gwOrig,gwMst);

    BasicGraph graph;
    string response = getLine("Do you want a random graph? (y/n)");
    if (response.size() > 0 && response[0] == 'y') {
        populateGraph(graph,true);
    } else {
        populateGraph(graph,false);
    }

    drawGraph(gwOrig,graph,"Original");

    BasicGraph mst;
    kruskal(graph,mst);
    drawGraph(gwMst, mst, "Minimum Spanning Tree");

    return 0;
}

void kruskal(BasicGraph& graph, BasicGraph &mst) {
    // first, copy the graph and remove the edges
    // This is so we can populate it later with the mst edges
    mst = graph;
    mst.clearEdges();
    // put each vertex into a 'cluster', initially containing only itself
    Map<Vertex*, Set<Vertex*>* > clusters;
    Set<Vertex*> allVertices = graph.getVertexSet();
    Vector<Set<Vertex*>* > allSets;   // for freeing later
    for (Vertex* v : allVertices) {
        Set<Vertex*>* set = new Set<Vertex*>();
        set->add(v);
        clusters[v] = set;
        allSets.add(set);
    }

    // put all edges into a priority queue, sorted by weight
    PriorityQueue<Edge*> pq;
    Set<Edge*> allEdges = graph.getEdgeSet();
    for (Edge* edge : allEdges) {
        pq.enqueue(edge, edge->cost);
    }

    // repeatedly pull min-weight edge out of PQ and add it to MST if its
    // endpoints are not already connected
    Set<Edge*> mstEdges;
    while (!pq.isEmpty()) {
        Edge* e = pq.dequeue();
        Set<Vertex*>* set1 = clusters[e->start];
        Set<Vertex*>* set2 = clusters[e->finish];
        if (set1 != set2) {
            mstEdges.add(e);

            // merge the two sets
            set1->addAll(*set2);
            for (Vertex* v : *set1) {
                Set<Vertex*>* setv = clusters[v];
                if (setv != set1) {
                    clusters[v] = set1;
                }
            }
        }
    }

    for (Set<Vertex*>* set : allSets) {
        delete set;
    }

    // populate the graph with the edges
    // We can't add the edge pointers directly
    // because that would cause trouble freeing later
    for (Edge *edge : mstEdges) {
        mst.addEdge(edge->start->name,edge->end->name,edge->cost,false);
    }
}

void drawGraph(GWindow &gw, BasicGraph &graph,string title) {
    // always start with the same random seed
    // so we always get the same drawing for the same
    // vertices
    if (!GRID_GRAPH) {
        setRandomSeed(1234);
    }
    // place the title there
    gw.setTitle(title);
    Map<Vertex*,GPoint> vertexLocations;
    int vertCount = 0; // for the grid
    for (Vertex *vert : graph.getVertexSet()) {
        int x,y;

        if (!GRID_GRAPH) {
            // randomly locate vertex on graph
            x = randomInteger(5,gw.getWidth()-6);
            y = randomInteger(5,gw.getHeight()-6);
        } else {
            // put in a staggerd grid
            const int NUMCOLS = 3;
            int widthApart = gw.getWidth() / (NUMCOLS + 1) - 10; // make a bit smaller for screen size
            int heightApart = gw.getHeight() / 6; // could fix this
            x = (widthApart + ((vertCount % NUMCOLS) + (vertCount / NUMCOLS)) * widthApart);
            y = ((vertCount / NUMCOLS + 1 + vertCount) * heightApart);
        }
        GPoint p(x,y);
        vertexLocations.add(vert,p);
        // place a dot there
        gw.fillOval(x,y,10,10);

        // place a label
        GLabel *gl = new GLabel(vert->name);
        gl->setFont("SansSerif-28");
        gw.add(gl,p.getX(),p.getY());
        vertCount++;
    }

    Set<Set<string>>seenAlready;
    for (Edge *edge : graph.getEdgeSet()) {
        Set<string>sortedEdgeSet;
        sortedEdgeSet.add(edge->start->name);
        sortedEdgeSet.add(edge->end->name);

        if (!seenAlready.contains(sortedEdgeSet)) {
            GPoint startPoint = vertexLocations[edge->start];
            GPoint endPoint = vertexLocations[edge->end];
            gw.drawLine(startPoint,endPoint);

            // find the 1/3 point of the line (midpoint would have many
            // overlapping points for the grid)
            int avgX = abs((startPoint.getX()*2 + endPoint.getX())/3.0);
            int avgY = abs((startPoint.getY()*2 + endPoint.getY())/3.0);
            GLabel *gl = new GLabel(doubleToString(edge->cost));
            gl->setFont("SansSerif-28");
            gw.add(gl,avgX,avgY);
            // add an unambiguous edge to seenAlready
            // so we don't put same undirected edge in twice
            seenAlready.add(sortedEdgeSet);
        }
    }
}

void adjustWindows(GWindow &gw1,GWindow &gw2) {
    gw1.setSize(600,700);
    gw2.setSize(600,700);
    gw1.repaint();
    gw2.setLocation(gw1.getLocation().getX()+gw1.getCanvasWidth(),
                    gw1.getLocation().getY());
}

void populateGraph(BasicGraph &graph, bool randomVerts) {
    if (!randomVerts) {
        // add some vertices and edges
        for (int i=0; i < 5; i++) {
            Vertex *v = new Vertex("" + charToString(i+'a'));
            graph.addVertex(v);
        }

        // add some edges with weights
        graph.addEdge("a","b",9,false);
        graph.addEdge("a","c",75,false);
        graph.addEdge("b","c",95,false);
        graph.addEdge("b","d",19,false);
        graph.addEdge("b","e",42,false);
        graph.addEdge("c","d",51,false);
        graph.addEdge("d","e",31,false);
    } else {
       // add 10 vertices
       for (int i=0; i < 10; i++) {
           Vertex *v = new Vertex("" + charToString(i+'a'));
           graph.addVertex(v);
       }
       // for each vertex, add up to three random edges
       Vector<Vertex *> allVerts;
       for (Vertex *v : graph.getVertexSet()) {
           allVerts.add(v);
       }
       for (Vertex *v : graph.getVertexSet()) {
           Set<Vertex *>usedAlready;
           usedAlready.add(v); // don't use yourself
           for (int i=0;i<3;i++) {
              int vertIndex = randomInteger(0,graph.size()-1);
              if (usedAlready.contains(allVerts[vertIndex])) {
                  continue; // ignore
              }
              Vertex *second = allVerts[vertIndex];
              // get a random cost
              int cost = randomInteger(1,100);
              // create an edge
              graph.addEdge(v,second,cost);
              usedAlready.add(second);
           }
       }
    }
}

