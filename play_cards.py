"""File:     play_cards.py
   Purpose:  Play blackjack

   Run:      python play_cards.py

   Input:    Number of players (including dealer)
             Player actions:  'h' (hit), 's' (stand)
   Output:   Prompts for input, players' hands, players' totals
   Note:     Cards are represented as tuples consisting of two strings
             strings:  Ranks are 'A', '2', . . . , '10', 'J', 'Q', 'K'
             Suits are 'C', 'D', 'H', 'S'
"""

from random import randint
from sys import exit

#----------------------------------------------------------------------
def print_card(card):
   """Print a single card"""
   print '(', card[0], ',', card[1], ')',

#----------------------------------------------------------------------
def create_deck():
   """Create a deck of cards"""
   ranks = ['A', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K']
   suits = ['C', 'D', 'H', 'S']
   deck = []
   for suit in suits:
      for rank in ranks:
         card = (rank, suit)
         deck.append(card)
   return deck

#----------------------------------------------------------------------
def shuffle_deck(deck):
   """Shuffle the deck by swapping pairs of cards"""
   for i in range(51):     # i ranges from 0 to 50
      j = randint(i+1,51)  # j ranges from i+1 to 51
      deck[i], deck[j] = deck[j], deck[i]

#----------------------------------------------------------------------
def print_deck(deck):
   """Print a deck of cards"""
   for card in deck:
      print_card(card)
      print

#----------------------------------------------------------------------
def eval_blackjack_hand(hand, rank_vals):
   """Return a list whose elements are the possible values of the
      blackjack hand, hand.
      rank_vals is a dictionary with values of the various ranks,
      An ace is stored as 1"""
   val = 0
   ace_count = 0
   for card in hand:
      rank = card[0]
      card_val = rank_vals[rank]
      if card_val > 1:
         val = val + card_val
      else:
         val = val + 1
         ace_count = ace_count+1

   val_list = [val]
   for i in range(ace_count):
      val_list.append(val + (i+1)*10)

   return val_list

#----------------------------------------------------------------------
def print_val_list(val_list):
   """Print the values in val_list"""
   print "The possible values for your hand are:"
   print "  ",
   for val in val_list:
      print val,
   print

#----------------------------------------------------------------------
def convert_str_to_hand(hand_str):
   """Convert a user-input string into a hand.  (Not used)"""
   hand = []
   str_list = hand_str.split()
   for i in range(0,len(str_list),2):
      rank = str_list[i]
      suit = str_list[i+1]
      hand.append((rank,suit))
   return hand

#----------------------------------------------------------------------
def deal_start_hands(players, deck):
   """Deal two cards to each player"""
   # Create an empty hand for each player
   hands = []
   for player in range(players):
      hands.append([])

   for which_card in range(2):
      for player in range(players):
         card = deal_card(deck)
         hands[player].append(card)
   return hands

#----------------------------------------------------------------------
def print_hand(hand):
   """Print the cards in a hand"""
   for card in hand:
      print_card(card)
   print

#----------------------------------------------------------------------
def show_hands(hands, show_hole_card):
   """Show each hand, hiding the hole card of the dealer if
      show_hole_card is False"""

   for player in range(len(hands)-1):
      print player, ":     ",
      print_hand(hands[player])

   print "Dealer: ",
   if not show_hole_card:
      hand = hands[len(hands)-1]
      print '( X , X )',
      p_hand = hand[1:len(hand)]
      print_hand(p_hand)
   else:
      print_hand(hands[len(hands)-1])

#----------------------------------------------------------------------
def menu(player, hand, rank_vals):
   """Print a menu showing the player's options"""
   print "You are player", player, ". ",
   val_list = eval_blackjack_hand(hand, rank_vals)
   print_val_list(val_list)
   print "You can:"
   print "   Take a hit (h)"
   print "   Stand (s)"

#----------------------------------------------------------------------
def deal_card(deck):
   """Deal one card from the deck"""
   if len(deck) == 0:
      print "Trying to deal from empty deck!"
      print "Bye"
      exit()
   card = deck[0]
   del deck[0]
   return card

#----------------------------------------------------------------------
def hit_hand(player, hand, hands, deck, rank_vals):
   """Get a card and add it to the player's hand.  Return True
      if the player has gone bust, False otherwise."""
   card = deal_card(deck)
   hand.append(card)
   print
   show_hands(hands, False)
   val_list = eval_blackjack_hand(hand, rank_vals)
   print_val_list(val_list)
   if min(val_list) > 21:
      print "You've gone bust!"
      print
      return True
   else:
      print
      return False

#----------------------------------------------------------------------
def play_hand(player, hands, deck, rank_vals):
   """Take hits until player stands or goes bust"""
   hand = hands[player]
   print
   menu(player, hand, rank_vals)
   show_hands(hands, False)
   cmd = raw_input("Enter a command (h, s):  ")
   busted = False
   while cmd != 's' and not busted:
      if cmd == 'h':
         busted = hit_hand(player, hand, hands, deck, rank_vals)
      elif cmd == 's':
         print "OK"
      else:
         print cmd, "isn't a valid option.  Please try again."
         menu(player, hand, rank_vals)
      if not busted:
         cmd = raw_input("Enter a command (h, s):  ")

#----------------------------------------------------------------------
def compute_hand_val(val_list):
   """Determine the value of the hand"""
   i = len(val_list)-1
   val = val_list[i]
   while i > 0 and val > 21:
      i = i-1
      val = val_list[i]
   return val
   
#----------------------------------------------------------------------
def play_dealer(hands, deck, rank_vals):
   """Play the dealer's hand"""
   dealer = len(hands)-1
   hand = hands[dealer]
   val_list = eval_blackjack_hand(hand, rank_vals)
   hand_val = compute_hand_val(val_list)
   print
   print "Dealer plays . . ."
   show_hands(hands, True)
   print "Hand =", hand_val
   while hand_val < 17:
      print
      c = raw_input("Hit any key to continue . . .")
      card = deal_card(deck)
      hand.append(card)
      print
      show_hands(hands, True)
      val_list = eval_blackjack_hand(hand, rank_vals)
      hand_val = compute_hand_val(val_list)
      print "Hand =", hand_val
      if hand_val > 21:
         print "Dealer went bust."
   print

#----------------------------------------------------------------------
def all_busted(hands, rank_vals):
   """See if all players other than the dealer have gone bust"""
   for hand in hands[0:len(hands)-1]:
      val_list = eval_blackjack_hand(hand, rank_vals)
      if min(val_list) <= 21:
         return False
   return True


#----------------------------------------------------------------------
def print_winner(p, p_val, p_blkjk, d_val, d_blkjk):
   """Determine who won -- player p or the dealer"""
   if p_val > 21:
      print p, "went bust.  Dealer wins"
   elif d_val > 21: 
      print p, "has",  p_val, ".  Dealer went bust. ", p, "wins."
   elif p_blkjk and d_blkjk:
      print p, "and the dealer have blackjack.  A tie."
   elif p_blkjk:
      print p, "has blackjack.  Dealer has", d_val, ". ", p, "wins."
   elif d_blkjk:
      print p, "has", p_val, ".  Dealer has blackjack.  Dealer wins."
   elif p_val > d_val:
      print p, "has", p_val, ".  Dealer has", d_val, ". ", p, "wins."
   elif p_val < d_val:
      print p, "has", p_val, ".  Dealer has", d_val, ".  Dealer wins."
   else:
      print p, "has", p_val, ".  Dealer has", d_val, ".  A tie."

#----------------------------------------------------------------------
def winners(hands, rank_vals):
   """Determine who won and who lost"""
   hand = hands[len(hands)-1]
   val_list = eval_blackjack_hand(hand, rank_vals)
   dealer_val = compute_hand_val(val_list)
   if dealer_val == 21 and len(hand) == 2:
      dealer_blackjack = True
   else:
      dealer_blackjack = False

   for player in range(len(hands)-1):
      hand = hands[player]
      val_list = eval_blackjack_hand(hand, rank_vals)
      player_val = compute_hand_val(val_list)
      if player_val == 21 and len(hand) == 2:
         player_blackjack = True
      else:
         player_blackjack = False
      print_winner(player, player_val, player_blackjack, 
            dealer_val, dealer_blackjack)


#----------------------------------------------------------------------
def play_game(players, deck, rank_vals):
   """Play a game of blackjack"""  

   hands = deal_start_hands(players, deck)

   show_hands(hands, False)
   print

   # Player number players-1 is the dealer
   for player in range(players-1):
      play_hand(player, hands, deck, rank_vals)

   if all_busted(hands, rank_vals):
      print 
      show_hands(hands, True)
      print "All players have gone bust"
   else:
      play_dealer(hands, deck, rank_vals)
      winners(hands, rank_vals)

#----------------------------------------------------------------------
if __name__ == "__main__":
   rank_vals = {'A':1, '2':2, '3':3, '4':4, '5':5, '6':6, '7':7, '8':8, '9':9, 
         '10':10, 'J':10, 'Q':10, 'K':10}
   
   deck = create_deck()
#  print "Original deck:"
#  print_deck(deck)
#  print
   
   shuffle_deck(deck)
#  print "Shuffled deck:"
#  print_deck(deck)
   
   players = int(raw_input("How many players (including dealer)?\n   "))
   play_game(players, deck, rank_vals)
   
   print "Bye!"
