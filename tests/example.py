from PyHex import Hex11

if __name__ == "__main__":
    hg = Hex11.HexGame()
    winner = -1

    for game in range(10000000):
        PyHex.init(hg)

        player = 0

        while PyHex.full_board(hg) == 0:
            position = PyHex.place_piece_randomly(hg, player)

            if PyHex.winner(hg, player, position):
                winner = player
                break

            player = 1 - player
        print(PyHex.print(hg))
        if hg.number_of_open_positions >= 75:
            print("\nPlayer %s wins!\n\n" % (winner, ))
            PyHex.print(hg)

