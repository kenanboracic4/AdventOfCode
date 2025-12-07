def prebroji_ukupan_broj_svjezih_id():

    try:
        with open('input.txt', 'r') as file:
            data = file.read().strip()
    except FileNotFoundError:
        print("Greška: Datoteka 'input.txt' nije pronađena.")
        return 0


    rasponi_str = data.split('\n\n')[0].split('\n')

    svjezi_rasponi = []


    for r_str in rasponi_str:
        r_str = r_str.strip()
        if not r_str or '-' not in r_str:
            continue

        try:
            pocetak, kraj = map(int, r_str.split('-'))
            svjezi_rasponi.append((pocetak, kraj))
        except ValueError:
            continue


    if not svjezi_rasponi:
        return 0


    svjezi_rasponi.sort(key=lambda x: x[0])

    spojeni_rasponi = []


    trenutni_pocetak, trenutni_kraj = svjezi_rasponi[0]

    for i in range(1, len(svjezi_rasponi)):
        sljedeci_pocetak, sljedeci_kraj = svjezi_rasponi[i]


        if sljedeci_pocetak <= trenutni_kraj + 1:

            trenutni_kraj = max(trenutni_kraj, sljedeci_kraj)
        else:

            spojeni_rasponi.append((trenutni_pocetak, trenutni_kraj))
            trenutni_pocetak, trenutni_kraj = sljedeci_pocetak, sljedeci_kraj


    spojeni_rasponi.append((trenutni_pocetak, trenutni_kraj))


    ukupan_broj_id = 0
    for pocetak, kraj in spojeni_rasponi:

        ukupan_broj_id += (kraj - pocetak + 1)

    return ukupan_broj_id


rezultat = prebroji_ukupan_broj_svjezih_id()
print(rezultat)