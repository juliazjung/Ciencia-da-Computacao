import tkinter as tk
from tkinter import filedialog

class ArquivoManager:
    def __init__(self, parent, callbackObj):
        self.caminhoArquivo = None
        self.callbackObj = callbackObj

        self.janela = tk.Toplevel(parent)
        self.janela.title("Seletor de imagem")
        self.janela.geometry("500x150")
        self.janela.transient(parent)
        self.janela.grab_set()
        
        self.criarWidgets()

    def criarWidgets(self):
        # Campo de texto que mostra o caminho
        tk.Label(self.janela, text="Arquivo selecionado:").pack(pady=5)
        self.arquivoEntrada = tk.Entry(self.janela, width=50)
        self.arquivoEntrada.pack(pady=5)

        # Botão p/ abrir os arquivos
        btnSelecionar = tk.Button(self.janela, text="Procurar arquivo...", command=self.selecionarArquivo)
        btnSelecionar.pack(pady=10)

        # Botão confirmar
        btnConfirmar = tk.Button(self.janela, text="Confirmar", command=self.confirmar)
        btnConfirmar.pack(pady=5)

    def selecionarArquivo(self):
        caminho = filedialog.askopenfilename(
            title="Selecione uma imagem",
            filetypes=(
                ("Imagens", "*.jpg *.jpeg *.png *.gif *.bmp *.tiff"),
                ("JPEG", "*.jpg *.jpeg"),
                ("PNG", "*.png")
            )
        )

        if caminho:
            self.arquivoEntrada.delete(0, tk.END)
            self.arquivoEntrada.insert(0, caminho)
            self.caminhoArquivo = caminho
    
    def confirmar(self):
        if self.caminhoArquivo:
            # Chama callback da janela principal
            self.callbackObj.atualizarArquivo(self.caminhoArquivo)
            self.janela.destroy()  # Fecha esta janela secundária

    def run(self):
        self.janela.mainloop()
