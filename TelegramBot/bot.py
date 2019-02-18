import telebot
from telebot import types

TOKEN = '680004388:AAGne98mFi2dLrovHRAd1HV_n91hL3qJVoA'
bot = telebot.TeleBot(TOKEN)

def listener(mensajes):
    for m in mensajes:
        chat_id = m.chat.id
        texto = m.text
        print('ID: ' + str(chat_id) + ' - MENSAJE: ' + texto)

@bot.message_handler(commands=['start'])
def search_username(message):
    f = open("usuarios", "r")
    lineas = f.readlines()
    enc = False
    for l in lineas:
        if enc == True:
            break
        laux = l.split(';')
        if(laux[0]==str(message.chat.id)):
            name = laux[1]
            for n in range(2,len(laux)-1):
                name += ' ' + laux[n]
            bot.reply_to(message, "Hey {}, how you doing?!".format(name))
            enc = True
    if enc == False:
        bot.send_message(message.chat.id, "Hi! I don't know about you. Tell me your name with the command:\n/name yourname.")
    f.close()

@bot.message_handler(commands=['name'])
def set_username(message):
    aux = message.text.split(' ')
    if len(aux)>1:
        name=aux[1]
        for n in range(2,len(aux)):
            name += ' ' + aux[n]
        bot.send_message(message.chat.id, "Registering with name \"{}\".".format(name))
        f = open("usuarios", 'a+')
        f.write("{};{};\n".format(message.chat.id, name))
        f.close()
        bot.send_message(message.chat.id, 'Done!')
    else:
        bot.send_message(message.chat.id, "You should specify a name! Try again.")

@bot.message_handler(commands=['help'])
def send_help(message):
    comandos=""
    f = open("comandos","r")
    lineas = f.readlines()
    for l in lineas:
        if l[0] != "#":
            comandos += l
    bot.reply_to(message, "Hey, the available commands are:\n\n"+comandos)

@bot.message_handler(commands=['test'])
def send_test(message):
    bot.send_message(message.chat.id, "The bot is ✅ ONLINE now. It does NOTHING actually 🙃.")


print('Bot iniciado')

bot.set_update_listener(listener)
bot.polling()

print('Cerrando...')
