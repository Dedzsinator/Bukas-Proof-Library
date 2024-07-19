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
        self.height = [0] * V
        self.excess = [0] * V

    def push(self, u, v, e):
        flow = min(self.excess[u], e.C - e.flow)
        e.flow += flow
        e.rev.flow -= flow
        self.excess[u] -= flow
        self.excess[v] += flow

    def relabel(self, u):
        min_height = float('inf')
        for e in self.adj[u]:
            if e.flow < e.C:
                min_height = min(min_height, self.height[e.v])
        self.height[u] = min_height + 1

    def discharge(self, u):
        while self.excess[u] > 0:
            for i, e in enumerate(self.adj[u]):
                if e.flow < e.C and self.height[u] == self.height[e.v] + 1:
                    self.push(u, e.v, e)
                    if self.excess[u] == 0:
                        break
            if self.excess[u] > 0:
                self.relabel(u)

    def push_relabel(self, source, dest):
        self.height[source] = self.V
        self.excess[source] = float('inf')
        for e in self.adj[source]:
            self.push(source, e.v, e)

        current = 0
        while current < self.V:
            u = current
            if u != source and u != dest:
                self.discharge(u)
            current += 1

        return self.excess[dest]

    # Other methods remain the same

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

        max_flow = graph.push_relabel(source, dest)

        # Megoldás generálások
        for i in range(self.height):
            for j in range(self.width):
                node = i * self.width + j
                if graph.BFS(source, node, [-1]*V):
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