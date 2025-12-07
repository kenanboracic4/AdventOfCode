def izracunaj_ukupan_zbir_ispravljeno():

    try:
        with open('input.txt', 'r') as file:
            redovi = file.readlines()
    except FileNotFoundError:
        print("Greška: Datoteka 'input.txt' nije pronađena.")
        return 0


    redovi = [red.rstrip('\n') for red in redovi]
    if not redovi:
        return 0

    max_duzina = max(len(red) for red in redovi)


    redovi = [red.ljust(max_duzina) for red in redovi]
    broj_redova = len(redovi)

    ukupan_zbir = 0
    trenutni_pocetak = 0


    for i in range(max_duzina + 1):


        je_separator = False
        if i == max_duzina:
            je_separator = True
        else:

            if all(redovi[r][i] == ' ' for r in range(broj_redova)):
                je_separator = True

        if je_separator and i > trenutni_pocetak:


            sirina_problema = i - trenutni_pocetak


            operacija_kolona = redovi[broj_redova - 1][trenutni_pocetak: i]


            if '*' in operacija_kolona:
                operacija = '*'
            elif '+' in operacija_kolona:
                operacija = '+'
            else:

                trenutni_pocetak = i + 1
                continue

            brojevi = []


            for r in range(broj_redova - 1):
                broj_str = redovi[r][trenutni_pocetak: i].strip()
                if broj_str:
                    try:
                        brojevi.append(int(broj_str))
                    except ValueError:
                        continue


            if brojevi:
                rezultat = 0
                if operacija == '+':
                    rezultat = sum(brojevi)
                elif operacija == '*':
                    rezultat = 1
                    for broj in brojevi:
                        rezultat *= broj

                ukupan_zbir += rezultat


            trenutni_pocetak = i + 1

        elif je_separator:

            trenutni_pocetak = i + 1

    return ukupan_zbir


rezultat = izracunaj_ukupan_zbir_ispravljeno()
print(rezultat)