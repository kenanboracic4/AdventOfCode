def simuliraj_uklanjanje_rolni(mreza):

    broj_redova = len(mreza)
    if broj_redova == 0:
        return 0


    mreza_lista = [list(red) for red in mreza]
    broj_kolona = len(mreza_lista[0])


    smjerovi = [
        (-1, -1), (-1, 0), (-1, 1),
        (0, -1), (0, 1),
        (1, -1), (1, 0), (1, 1)
    ]

    ukupno_uklonjeno = 0

    while True:
        rolne_za_uklanjanje = []


        for r in range(broj_redova):
            for k in range(broj_kolona):

                if mreza_lista[r][k] == '@':
                    susjedne_rolne = 0


                    for dr, dk in smjerovi:
                        susjed_r, susjed_k = r + dr, k + dk

                        if 0 <= susjed_r < broj_redova and 0 <= susjed_k < broj_kolona:


                            if mreza_lista[susjed_r][susjed_k] == '@':
                                susjedne_rolne += 1


                    if susjedne_rolne < 4:
                        rolne_za_uklanjanje.append((r, k))


        if not rolne_za_uklanjanje:

            break


        for r, k in rolne_za_uklanjanje:
            mreza_lista[r][k] = '.'
            ukupno_uklonjeno += 1

    return ukupno_uklonjeno



try:
    with open('input.txt', 'r') as file:
        ulazna_mreza = [linija.strip() for linija in file.readlines() if linija.strip()]
except FileNotFoundError:
    print("Greška: Datoteka 'input.txt' nije pronađena.")
    exit()

rezultat = simuliraj_uklanjanje_rolni(ulazna_mreza)
print(rezultat)