# Grafy - Aplikacja do wizualizacji grafów

Aplikacja desktopowa do wizualizacji i analizy grafów, napisana w C++ z użyciem biblioteki wxWidgets.

## Opis programu

Aplikacja umożliwia tworzenie, edycję i analizę grafów z wagami. Program wspiera import i eksport grafów w formacie GraphML, wizualizację algorytmów (BFS, DFS, Dijkstry), oraz wyświetlanie macierzy sąsiedztwa i incydencji.

## Funkcje

- **Tworzenie grafów** - dodawanie i usuwanie wierzchołków oraz krawędzi
- **Wagi krawędzi** - możliwość przypisania wagi do każdej krawędzi
- **Import/Eksport** - obsługa formatu GraphML
- **Algorytmy**:
  - Przeszukiwanie w głąb (DFS)
  - Przeszukiwanie wszerz (BFS)
  - Algorytm Dijkstry (najkrótsza ścieżka)
- **Macierze**:
  - Macierz sąsiedztwa
  - Macierz incydencji
- **Eksport danych** - zapisywanie wyników do pliku tekstowego
- **Przykładowe grafy** - dołączone gotowe przykłady grafów

## Wymagania

- Windows
- wxWidgets (do kompilacji ze źródła)

## Instalacja

Pobierz i uruchom `GrafyProjektInstalator.exe` ze strony releases.

## Kompilacja ze źródeł

1. Otwórz plik projektu `Grafy.cbp` w Code::Blocks
2. Skonfiguruj ścieżkę do wxWidgets w ustawieniach kompilatora
3. Zbuduj projekt (Build → Build)

## Format plików

Program obsługuje format GraphML. Przykładowe pliki:
- `PrzykladowyGraf_1(3 wierzcholki).graphml`
- `PrzykladowyGraf_2(25 wierzcholkow).graphml`
- `PrzykladowyGraf_3(35 wierzcholkow).graphml`
- `PrzykladowyGraf_4(40 wierzcholkow).graphml`
- `europa.graphml`

## Autor

- Maja Darczuk
- Jan Walkiewicz

## Licencja

Projekt na potrzeby zaliczenia przedmiotu.
