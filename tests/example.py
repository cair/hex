from PyHex import Hex11 as Hex

if __name__ == "__main__":
    hg = Hex.HexGame()
    winner = -1

    for game in range(10000000):
        Hex.init(hg)

        player = 0

        while Hex.full_board(hg) == 0:
            position = Hex.place_piece_randomly(hg, player)

            if Hex.winner(hg, player, position):
                winner = player
                break

            player = 1 - player

        if hg.number_of_open_positions >= 75:
            print("\nPlayer %s wins!\n\n" % (winner, ))
            Hex.print(hg)

