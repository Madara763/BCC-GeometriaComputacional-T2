import sys
import matplotlib.pyplot as plt

def ler_dados_arquivo(caminho_arquivo):
    with open(caminho_arquivo, 'r') as f:
        linhas = f.readlines()

    n, f = map(int, linhas[0].split())
    vertices = [tuple(map(int, linha.split())) for linha in linhas[1:n+1]]
    faces_raw = [list(map(int, linha.split())) for linha in linhas[n+1:n+1+f]]
    faces = [[idx - 1 for idx in face] for face in faces_raw]  # ajustar para base 0

    return vertices, faces

def main():
    if len(sys.argv) != 2:
        print("Uso: python3 malha_plot.py <arquivo_entrada>")
        sys.exit(1)

    caminho_arquivo = sys.argv[1]

    try:
        vertices, faces = ler_dados_arquivo(caminho_arquivo)
    except Exception as e:
        print(f"Erro ao ler o arquivo: {e}")
        sys.exit(1)

    # Plotar os vértices
    plt.figure(figsize=(8, 8))
    for i, (x, y) in enumerate(vertices):
        plt.plot(x, y, 'ko')
        plt.text(x + 0.1, y + 0.1, str(i + 1), fontsize=9, color='blue')

    # Plotar as faces
    for face in faces:
        face_coords = [vertices[idx] for idx in face]
        face_coords.append(face_coords[0])  # Fechar o polígono
        xs, ys = zip(*face_coords)
        plt.plot(xs, ys, linestyle='-', marker='', color='gray')

    plt.title("Malha DCEL - Vértices e Faces")
    plt.axis('equal')
    plt.grid(True)
    plt.show()

if __name__ == '__main__':
    main()
