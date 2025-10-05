import os
import tkinter as tk
from tkinter import messagebox, ttk
from PIL import Image, ImageTk
from ProcessamentoImagem import ProcessamentoImagem

class ImagemManager:
    def __init__(self, parent, caminho):
        self.caminhoArquivo = caminho
        self.janela = parent
        self.janela.title("Processamento de imagens")
        self.janela.geometry("1100x600")
        self.processamentoImagem = ProcessamentoImagem(caminho)
        self._setup_ui()

    def _setup_ui(self):
        # Configura toda a interface do usuário
        self._criar_frame_imagem()
        self._criar_secoes_controles()

    def _criar_frame_imagem(self):
        # Cria o frame para exibição da imagem
        self.imagemFrame = tk.Frame(self.janela, bg="white", relief=tk.SUNKEN, bd=2)
        self.imagemFrame.pack(pady=10, padx=10, fill=tk.BOTH, expand=True)

        self.imagemLabel = tk.Label(
            self.imagemFrame, 
            text="Selecione uma imagem", 
            bg="white", fg="gray", font=("Arial", 12)
        )
        self.imagemLabel.pack(expand=True)
        self.carregarImagem()

    def _criar_secoes_controles(self):
        # Cria as seções de controles lado a lado
        frame_principal = tk.Frame(self.janela)
        frame_principal.pack(pady=10, padx=10, fill=tk.BOTH, expand=True)

        self._criar_secao_roteamento(frame_principal)
        self._criar_secao_mascara_ruido(frame_principal)
        self._criar_secao_operacoes(frame_principal)        

    def _criar_secao_roteamento(self, parent):
        # Cria a seção de roteamento e espalhamento
        frame = ttk.LabelFrame(parent, text=" Roteamento e Espalhamento ", padding=10)
        frame.pack(side=tk.LEFT, padx=(0, 5), fill=tk.BOTH, expand=True)

        botoes_roteamento = [
            ("Rotacionar 90° a direita", self.processamentoImagem.rotacao90Direita),
            ("Rotacionar 90° a esquerda", self.processamentoImagem.rotacao90Esquerda),
            ("Espelhar na horizontal", self.processamentoImagem.espelhamentoHorizontal),
            ("Espelhar na vertical", self.processamentoImagem.espelhamentoVertical),
        ]

        for i, (texto, comando) in enumerate(botoes_roteamento):
            btn = tk.Button(
                frame, 
                text=texto,
                command=lambda cmd=comando: self._executar_comando(cmd)
            )
            btn.grid(row=i//2, column=i%2, padx=5, pady=5, sticky="ew")

         # Botão recriar
        btn_recriar = tk.Button(frame, text="Recriar imagem", command=self.recarregarImagem)
        btn_recriar.grid(row=len(botoes_roteamento), column=0, columnspan=2, padx=5, pady=10, sticky="ew")

        self._configurar_grid(frame)

    def recarregarImagem (self):
        self.processamentoImagem.recarregarImagem()
        self.carregarImagem()

    def _criar_secao_operacoes(self, parent):
        # Cria a nova seção de operações
        frame = ttk.LabelFrame(parent, text=" Operações ", padding=10)
        frame.pack(side=tk.LEFT, padx=(5, 0), fill=tk.BOTH, expand=True)

        botoes_operacoes = [
            ("Roberts", self.processamentoImagem.operadorRoberts),
            ("Canny", self.processamentoImagem.operadorCanny),
            ("Op 3", self.processamentoImagem.operadorRoberts),
            ("Op 4", self.processamentoImagem.operadorRoberts),
        ]

        for i, (texto, comando) in enumerate(botoes_operacoes):
            btn = tk.Button(
                frame, 
                text=texto,
                command=lambda cmd=comando: self._executar_comando(cmd)
            )
            btn.grid(row=i//2, column=i%2, padx=5, pady=5, sticky="ew")

        self._configurar_grid(frame)

    def _criar_secao_mascara_ruido(self, parent):
        # Cria a seção de máscara e redução de ruído
        frame = ttk.LabelFrame(parent, text=" Máscara e Redução de Ruído ", padding=10)
        frame.pack(side=tk.LEFT, padx=(5, 0), fill=tk.BOTH, expand=True)

        # Configurações dos comboboxes
        configuracoes = [
            ("Tamanho da máscara:", "comboTamMasc", [
                "3x3", "5x5", "7x7", "9x9", "11x11", "13x13", 
                "15x15", "17x17", "19x19", "21x21"
            ]),
            ("Aplicação da máscara:", "comboAplMasc", ["Coluna", "Linha"]),
            ("Redução de ruído:", "comboRedRuido", ["Mediana", "Moda"]),
        ]

        for i, (label_text, attr_name, valores) in enumerate(configuracoes):
            label = ttk.Label(frame, text=label_text)
            label.grid(row=i, column=0, padx=5, pady=5, sticky="w")

            combobox = ttk.Combobox(frame, values=valores)
            combobox.grid(row=i, column=1, padx=5, pady=5, sticky="ew")
            setattr(self, attr_name, combobox)

        # Botão aplicar
        btn_aplicar = tk.Button(frame, text="Aplicar", command=self.aplicarMascara)
        btn_aplicar.grid(row=len(configuracoes), column=0, columnspan=2, padx=5, pady=10, sticky="ew")

        self._configurar_grid(frame)

    def _configurar_grid(self, frame):
        # Configura grid com colunas de peso igual
        frame.columnconfigure(0, weight=1)
        frame.columnconfigure(1, weight=1)

    def _executar_comando(self, comando):
        # Executa comando e atualiza a imagem
        comando()
        self.carregarImagem()

    def carregarImagem(self):
        # Carrega e exibe a imagem atual
        try:
            image = self.processamentoImagem.imagemAtual
            max_size = (300, 300)
            image.thumbnail(max_size, Image.Resampling.LANCZOS)
            
            self.imagem = ImageTk.PhotoImage(image)
            self.imagemLabel.configure(image=self.imagem, text="")

        except Exception as e:
            messagebox.showerror("Erro", f"Não foi possível carregar a imagem:\n{str(e)}")

    def aplicarMascara(self):
        # Aplica a máscara de redução de ruído
        campos_obrigatorios = {
            "tamanho": self.comboTamMasc.get(),
            "aplicacao": self.comboAplMasc.get(),
            "reducao": self.comboRedRuido.get()
        }

        if not all(campos_obrigatorios.values()):
            messagebox.showwarning("Aviso", "Preencha todos os campos!")
            return
        
        self.processamentoImagem.aplicarReducaoRuido(
            campos_obrigatorios["tamanho"],
            campos_obrigatorios["aplicacao"], 
            campos_obrigatorios["reducao"]
        )
        self.carregarImagem()

    def run(self):
        # Inicia a aplicação
        self.janela.mainloop()