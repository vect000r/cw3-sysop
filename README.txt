Rozwiązanie przez: BARTŁOMIEJ GALEK

Program cw3a uruchamia sie z argumentami wywoływania odpowiednio:
-argument 1: wybór sposobu obsługi sygnału spośród 1 2 3 gdzie 1 to domyślna obsługa, 2 to ignorowanie, 3 to przechwycenie sygnału
-argument 2: numer sygnału który chcemy wysłać do programu 

Program cw3b w procesie potomnym uruchamia program cw3a

Program cw3c w procesie potomnym uruchamia program cw3c1 i wysyła sygnał do grupy procesów utworzonych przez cw3c1. cw3c1 wywołuje funkcję fork 3 razy i w procesach potomnych uruchamia program cw3a z obsługą procesów.