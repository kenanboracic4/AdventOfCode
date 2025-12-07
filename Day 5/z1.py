def prebroji_svjeze_sastojke():

    try:
        with open('input.txt', 'r') as file:
            data = file.read().strip()
    except FileNotFoundError:
        print("Greška: Datoteka 'input.txt' nije pronađena.")
        return 0


    dijelovi = data.split('\n\n')


    rasponi_str = dijelovi[0].split('\n')
    dostupni_id_str = dijelovi[1].split('\n')

    svjezi_rasponi = []


    for r_str in rasponi_str:
        r_str = r_str.strip()
        if not r_str:
            continue

        try:
            pocetak, kraj = map(int, r_str.split('-'))
            svjezi_rasponi.append((pocetak, kraj))
        except ValueError:
            continue

    dostupni_id = []


    for id_str in dostupni_id_str:
        id_str = id_str.strip()
        if not id_str:
            continue

        try:
            dostupni_id.append(int(id_str))
        except ValueError:
            continue

    broj_svjezih = 0


    for id_sastojka in dostupni_id:
        je_svjez = False


        for pocetak, kraj in svjezi_rasponi:

            if pocetak <= id_sastojka <= kraj:
                je_svjez = True
                break

        if je_svjez:
            broj_svjezih += 1

    return broj_svjezih


rezultat = prebroji_svjeze_sastojke()
print(rezultat)