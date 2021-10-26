sdi1800056 sdi1800072

* Έχει γίνει χρήση cmake. Για να γίνει compile το πρόγραμμα θα πρέπει να εκτελεστεί η
  εντολή `cmake .` και η εντολή `make`. Έτσι θα δημιουργηθεί το εκτελέσιμο run_tests.

* Για το testing έχουμε χρησιμοποιήσει τη βιβλιοθήκη catch2. To source code βρίσκεται στον φάκελο
  lib, για να μπορεί να χρησιμοποιηθεί και σε υπολογιστές που δεν την έχουν εγκατεστημένη.

* Στο CMakeLists.txt έχω προσθέσει και sanitization για address, leak και undefined. Αυτά μαζί με τα
  warnings του compiler που έχω ενεργοποιημένα προσφέρουν μία ασφάλεια για την ποιότητα του κώδικα.

* Ένα αρχείο με documents πρέπει να περιέχει μία λέξη σε κάθε γραμμή.

* Ένα αρχείο με queries πρέπει και αυτό να περιέχει μία λέξη σε κάθε γραμμή. Για να δημιουργήσεις 2o
  query στο ίδιο αρχείο, πρέπει να αφήσεις μία κενή γραμμή.

* Έχω χρησιμοποιήσει templates για να μπορώ να φτιάξω containers με διαφορετικό τύπο δεδομένων κάθε
  φορά.

* vector class: είναι μία απομίμηση του std::vector. Έχω δημιουργήσει iterators για πιο εύκολη
  χρήση.

* forward_list class: μία single linked list. Έχω δημιουργήσει και εδώ iterators.

* unordered_map class: ένα hash_table.

* file_reader class:
  Διαβάζει αρχεία και δημιουργεί vector με τα δεδομένα τους. Μπορεί να φτιάξει και έναν vector που
  να περιέχει την κάθε λέξη μόνο μία φορά, αν του ζητηθεί με την βοήθεια ενός unordered_map. Για
  μειώσω τα allocations που γίνονται, μετράω πρώτα το μέγεθος του αρχείο που μου δώθηκε. Έτσι κάνω
  ένα μεγάλο allocation αντί για πολλά μικρά.

* inverted_search_engine class:
  Μία abstract class. Παίρνει ως παράμετρο έναν vector με queries. Δημιουργεί ένα hash map το οποίο
  έχει ως κλειδί ένα string* και για value ένα vector από ints. Ο vector με int αντιπροσωπεύει τα
  queries στα οποία περιέχεται αυτή η λέξη. Έχει επίσης και ένα vector από string* στο οποίο είναι
  οι ξεχωριστές λέξεις όλων των queries.

* exact_matching_engine class:
  Είναι παιδί της inverted_search_engine class. Υλοποιεί την αναζήτηση με exact matching. Για να το
  πετύχει αυτό χρησιμοποιεί το hash map της inverted_search_engine class.
