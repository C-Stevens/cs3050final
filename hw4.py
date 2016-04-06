class node:
    def __init__(self, index):
        self.index = index
        self.weight = -1
        self.edges = []
    def setWeight(self, weight):
        self.weight = weight
    def addEdge(self, index, indexWeight):
        index.setWeight(indexWeight)
        self.edges.append(index)

class graph:
    def __init__(self, number_of_nodes):
        self.number_of_nodes = number_of_nodes
        self.nodes = [None] * number_of_nodes
        for i in range(number_of_nodes):
            self.nodes[i] = node(i + 1)
    def getNode(self, index):
        return self.nodes[index - 1]
    def addEdge(self, fromNode, toNode, weight):
        self.getNode(fromNode).addEdge(toNode, weight)
        #self.getNode(toNode).addEdge(fromNode, weight) Remove because undirected graph?
    def getNeighbors(self, index):
        return self.getNode(index).edges




def traverseFromOne(g):
    # Initialize tracking stuff
    visited = [False] * g.number_of_nodes # Tracks visitedness
    results = [-1] * g.number_of_nodes # Tracks distance from node 1

    # Set up queue and initial node
    q = [(1, 0)] # Queue starts with node 1, 0 hops from itself
    visited[0] = True # We've already visited node 1 (0-based array)
    results[0] = 0 # We already know that node 1 is 0 hops away from itself (0-based array)

    # BFS implementation
    while q:
        currentAndHops = q.pop()
        current = currentAndHops[0]
        hops = currentAndHops[1]
        results[current - 1] = hops
        neighbors = g.getNeighbors(current)
        for neighbor in neighbors:
            if not visited[neighbor - 1]:
                q.append((neighbor, hops + 1))
                visited[neighbor - 1] = True

    # We're done, print results
    for i, hops in enumerate(results):
        print('Node', i + 1, 'is', hops, 'away from node 1')



g = graph(6)
g.addEdge(2, 3, 10)
g.addEdge(1, 4, 7)
g.addEdge(1, 3, 3)
g.addEdge(3, 4, 3)
g.addEdge(4, 5, 1)
traverseFromOne(g)