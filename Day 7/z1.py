def prebroji_cijepanja_snopa_bez_komentara(mreza):
    broj_redova = len(mreza)
    if broj_redova == 0:
        return 0

    broj_kolona = len(mreza[0])

    start_kolona = -1
    for k in range(broj_kolona):
        if mreza[0][k] == 'S':
            start_kolona = k
            break

    if start_kolona == -1:
        return 0

    snopovi_za_obradu = [(0, start_kolona)]
    posjeceni_cjepaci = set()
    ukupno_cijepanja = 0

    while snopovi_za_obradu:
        r_start, k = snopovi_za_obradu.pop(0)

        for r in range(r_start + 1, broj_redova):

            if mreza[r][k] == '.':
                continue

            elif mreza[r][k] == '^':

                if (r, k) not in posjeceni_cjepaci:
                    ukupno_cijepanja += 1
                    posjeceni_cjepaci.add((r, k))

                if k - 1 >= 0:
                    snopovi_za_obradu.append((r, k - 1))

                if k + 1 < broj_kolona:
                    snopovi_za_obradu.append((r, k + 1))

                break

            elif mreza[r][k] == 'S':
                break

    return ukupno_cijepanja


try:
    with open('input.txt', 'r') as file:
        ulazna_mreza = [linija.strip() for linija in file.readlines() if linija.strip()]
except FileNotFoundError:
    print("Greška: Datoteka 'input.txt' nije pronađena.")
    exit()

rezultat = prebroji_cijepanja_snopa_bez_komentara(ulazna_mreza)
print(rezultat)