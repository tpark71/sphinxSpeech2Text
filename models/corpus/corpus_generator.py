templates = [
    "Show me to room {{ROOM}}",
    "How do I get to {{ROOM}}",
    "How do I get to room {{ROOM}}",
    "Show me to {{ROOM}}",
    "Where is {{ROOM}}",
    "Take me to room {{ROOM}}",
    "Take me to {{ROOM}}",
    "Move to room {{ROOM}}",
    "Move to {{ROOM}}"
]

def append_general_phrases(corpus_file):
    phrases_file = open('general-phrases.txt', 'r')
    for phrase in phrases_file:
        phrase = phrase.strip()
        corpus_file.write(phrase + '\n')
    phrases_file.close()

def generate_phrases_for_room(room_number):
    output = []
    for template in templates:
        phrase = template.replace("{{ROOM}}", room_number)
        output.append(phrase)
    return output

def read_in_rooms(corpus_file):
    room_file = open('rooms.txt', 'r')
    for room in room_file:
        room = room.strip()
        phrases = generate_phrases_for_room(room)
        for phrase in phrases:
            corpus_file.write(phrase + '\n')
    room_file.close()


corpus_file = open("corpus.txt", "w")

append_general_phrases(corpus_file)
read_in_rooms(corpus_file)

corpus_file.close()
