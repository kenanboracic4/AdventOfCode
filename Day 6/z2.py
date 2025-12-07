def izracunaj_ukupan_zbir_desno_nalijevo():

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
    svi_problemi = []


    for i in range(max_duzina + 1):


        je_separator = (i == max_duzina) or all(redovi[r][i] == ' ' for r in range(broj_redova))

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


            for k in range(sirina_problema):


                broj_str = ""
                za_parse_kolona = ""

                # Sastavljanje vertikalnog stringa cifara
                for r in range(broj_redova - 1):
                    za_parse_kolona += redovi[r][trenutni_pocetak + k]

                for r in range(broj_redova - 1):

                    segment = redovi[r][trenutni_pocetak: i].strip()
                    if segment:

                        try:
                            brojevi.append(int(segment))
                        except ValueError:
                            pass


            broj_cifara = broj_redova - 1

            vertikalni_brojevi = []


            for k in range(sirina_problema):

                cifre_str = ""

                for r in range(broj_redova - 1):
                    cifra = redovi[r][trenutni_pocetak + k]
                    if cifra != ' ':
                        cifre_str += cifra

                if cifre_str:
                    try:
                        vertikalni_brojevi.append(int(cifre_str))
                    except ValueError:
                        pass


            if vertikalni_brojevi:
                rezultat = 0
                if operacija == '+':
                    rezultat = sum(vertikalni_brojevi)
                elif operacija == '*':
                    rezultat = 1
                    for broj in vertikalni_brojevi:
                        rezultat *= broj


                svi_problemi.append(rezultat)


            trenutni_pocetak = i + 1

        elif je_separator:

            trenutni_pocetak = i + 1


    ukupan_zbir = sum(svi_problemi)

    return ukupan_zbir


rezultat = izracunaj_ukupan_zbir_desno_nalijevo()
print(rezultat)