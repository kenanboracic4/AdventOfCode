def prebroji_vremenske_linije_bez_komentara(mreza):
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

    dp = [[0] * broj_kolona for _ in range(broj_redova)]

    dp[0][start_kolona] = 1

    for r in range(broj_redova):
        for k in range(broj_kolona):

            if dp[r][k] == 0:
                continue

            trenutni_broj_linija = dp[r][k]

            if r == broj_redova - 1:
                continue

            r_next = r + 1

            element_next = mreza[r_next][k]

            if element_next == '.':
                dp[r_next][k] += trenutni_broj_linija

            elif element_next == '^':
                k_left = k - 1
                if k_left >= 0:
                    dp[r_next][k_left] += trenutni_broj_linija

                k_right = k + 1
                if k_right < broj_kolona:
                    dp[r_next][k_right] += trenutni_broj_linija

            elif element_next == 'S' and r_next > 0:
                 dp[r_next][k] += trenutni_broj_linija

    ukupno_aktivnih_linija = 0

    for k in range(broj_kolona):
        ukupno_aktivnih_linija += dp[broj_redova - 1][k]

    return ukupno_aktivnih_linija


try:
    with open('input.txt', 'r') as file:
        ulazna_mreza = [linija.strip() for linija in file.readlines() if linija.strip()]
except FileNotFoundError:
    print("Greška: Datoteka 'input.txt' nije pronađena.")
    exit()

rezultat = prebroji_vremenske_linije_bez_komentara(ulazna_mreza)
print(rezultat)