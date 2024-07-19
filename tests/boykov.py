import os
import sys
import cv2
import numpy as np
import concurrent.futures
from collections import defaultdict
import queue


class Edge:
    def __init__(self, v, flow, C, rev):
        self.v = v
        self.flow = flow
        self.C = C
        self.rev = rev

class Graph:
    def __init__(self, V):
        self.adj = defaultdict(list)
        self.V = V

    def add_edge(self, u, v, C):
        a = Edge(v, 0, C, len(self.adj[v]))
        b = Edge(u, 0, 0, len(self.adj[u]))
        self.adj[u].append(a)
        self.adj[v].append(b)

    def BFS(self, s, t, parent):
        visited = [False] * (self.V)
        q = queue.Queue()
        q.put(s)
        visited[s] = True
        while not q.empty():
            u = q.get()
            for i, e in enumerate(self.adj[u]):
                if visited[e.v] == False and e.flow < e.C:
                    q.put(e.v)
                    visited[e.v] = True
                    parent[e.v] = (u, i)
        return True if visited[t] else False

    def BoykovKolmogorov(self, source, dest):
        parent = [-1] * (self.V)
        max_flow = 0
        while self.BFS(source, dest, parent):
            path_flow = float("Inf")
            s = dest
            while s != source:
                u, i = parent[s]
                path_flow = min(path_flow, self.adj[u][i].C - self.adj[u][i].flow)
                s = parent[s][0]
            max_flow += path_flow
            v = dest
            while v != source:
                u, i = parent[v]
                self.adj[u][i].flow += path_flow
                self.adj[v][self.adj[u][i].rev].flow -= path_flow
                v = parent[v][0]
        return max_flow

class ImageSegmentation:
    def __init__(self, img, output_dir, img_name):
        self.image = img
        self.height, self.width, _ = img.shape
        self.foreground = np.zeros_like(img)
        self.background = np.zeros_like(img)
        self.output_dir = output_dir
        self.img_name = img_name

    def segment(self, bg_threshold):
        V = self.width * self.height + 2
        graph = Graph(V)

        source = V - 2
        dest = V - 1

        for i in range(self.height):
            for j in range(self.width):
                node = i * self.width + j
                intensity = np.mean(self.image[i, j])
                if intensity <= bg_threshold:
                    graph.add_edge(source, node, sys.maxsize)
                else:
                    graph.add_edge(node, dest, sys.maxsize)
                if i > 0:
                    graph.add_edge(node, (i - 1) * self.width + j, 1)
                if i < self.height - 1:
                    graph.add_edge(node, (i + 1) * self.width + j, 1)
                if j > 0:
                    graph.add_edge(node, i * self.width + (j - 1), 1)
                if j < self.width - 1:
                    graph.add_edge(node, i * self.width + (j + 1), 1)

        # Max flow using Boykov-Kolmogorov algorithm
        max_flow = graph.BoykovKolmogorov(source, dest)

        # Segmentation based on max flow
        for i in range(self.height):
            for j in range(self.width):
                node = i * self.width + j
                if graph.BFS(source, node, [-1] * V):
                    self.foreground[i, j] = self.image[i, j]
                else:
                    self.background[i, j] = self.image[i, j]

        cv2.imwrite(os.path.join(self.output_dir, f"{self.img_name}_fg.jpg"), self.foreground)
        cv2.imwrite(os.path.join(self.output_dir, f"{self.img_name}_bg.jpg"), self.background)

def process_image(image_path):
    image = cv2.imread(image_path)
    if image is None:
        print("Hiba! Nemjó a kép url:", image_path)
        return

    # Megállapítjuk a kép pixeleinek átlagos intenzitását
    bg_threshold = np.mean(image)

    img_name = os.path.splitext(os.path.basename(image_path))[0]

    segmentation = ImageSegmentation(image, "res", img_name)
    segmentation.segment(bg_threshold)

    print(f"Alany kivágva a {img_name} fileból és lementve ide: res/{img_name}_fg.jpg")
    print(f"Háttér kivágva a {img_name} fileból és lementve ide: res/{img_name}_bg.jpg")

def main():
    if len(sys.argv) < 2:
        print(f"Használat: {sys.argv[0]} <képUrl1> <képUrl2> ...")
        return

    image_paths = sys.argv[1:]

    os.makedirs("res", exist_ok=True)

    with concurrent.futures.ThreadPoolExecutor() as executor:
        # minden képet külön szálban dolgozunk fel
        executor.map(process_image, image_paths)

if __name__ == "__main__":
    main()