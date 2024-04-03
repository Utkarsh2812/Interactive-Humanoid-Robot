import serial  # Import the serial module for communication with Arduino
import time  # Import the time module for delays
import pyttsx3  # Import the pyttsx3 module for text-to-speech conversion
import speech_recognition as sr  # Import the speech_recognition module for speech recognition
import openai  # Import the openai module for AI chat completion

# Initialize the serial connection with Arduino
ser = serial.Serial('COM9', 9600)
time.sleep(2)  # Delay for 2 seconds to allow Arduino to initialize

# Set up OpenAI API key
openai.api_key = 'your api key over here'

# Initialize the text-to-speech engine
engine = pyttsx3.init()

# Initialize the speech recognizer
r = sr.Recognizer()

# Function to speak the given text
def speak_text(text):
    engine.say(text)
    engine.runAndWait()

# Function to transcribe audio to text
def transcribe_audio_to_txt(filename):
    recognizer = sr.Recognizer()  # Initialize the speech recognizer
    with sr.AudioFile(filename) as source:  # Open the audio file
        audio = recognizer.record(source)  # Record the audio from the file
    try:
        return recognizer.recognize_google(audio)  # Transcribe the audio to text using Google Speech Recognition
    except Exception as e:
        print('Skipping Unknown Error:', e)  # Print the error message if an exception occurs

# Function to generate a response using OpenAI ChatCompletion
def generate_response(prompt):
    response = openai.ChatCompletion.create(
        model="gpt-3.5-turbo",
        messages=[
            {"role": "system", "content": "You are a helpful assistant."},  # System message
            {"role": "user", "content": prompt},  # User message with prompt
        ]
    )
    return response['choices'][0]['message']['content']  # Return the generated response

# Function to handle the response system
def response_system():
    while True:
        print('Say "Hello" to begin recording...')

        # Start recording audio from microphone
        with sr.Microphone() as source:
            recognizer = sr.Recognizer()
            recognizer.energy_threshold = 300
            audio = recognizer.listen(source, phrase_time_limit=None, timeout=None)

            try:
                # Convert speech to text
                transcription = recognizer.recognize_google(audio)  # Use Google Speech Recognition to convert audio to text

                # Save audio to file
                filename = 'Input.wav'  # Set the filename for saving the audio
                print('What is your Query?..')  # Prompt the user for their query
                with sr.Microphone() as source:  # Use the microphone as the audio source
                    recognizer = sr.Recognizer()  # Initialize the speech recognizer
                    recognizer.energy_threshold = 300  # Set the energy threshold for audio recognition
                    source.pause_threshold = 1  # Set the pause threshold for audio recognition
                    audio = recognizer.listen(source, phrase_time_limit=None, timeout=None)  # Listen for audio input
                    with open(filename, 'wb') as f:  # Open the file in write binary mode
                        f.write(audio.get_wav_data())  # Write the audio data to the file

                # Transcribe audio to text
                text = transcribe_audio_to_txt(filename)
                if text:
                    print(f"Word Spoken: {text}")

                    # Generate response using OpenAI ChatCompletion
                    response = generate_response(text)
                    print(f"Word Recognized: {response}")

                    # Speak the response
                    speak_text(response)
            except Exception as e:
                print('Error occurred: {}'.format(e))

            # Ask user to continue or quit
            choice = input("Press 'q' to quit or any other key to continue: ")
            if choice.lower() == 'q':
                break

# Function to handle humanoid motions
def humanoid_motions():
    while True:
        try:
            with sr.Microphone() as source2:
                r.adjust_for_ambient_noise(source2, duration=0.2)  # Adjust for ambient noise
                audio2 = r.listen(source2)  # Listen for audio input
                MyText = r.recognize_google(audio2)  # Convert speech to text
                MyText = MyText.lower()  # Convert text to lowercase

                print("Did you say ", MyText)

                ser.write(MyText.encode())  # Send text to Arduino
                time.sleep(0.5)  # Delay for 0.5 seconds

                speak_text(MyText)  # Speak the recognized text

                choice = input("Press 'k' to quit or any other key to continue: ")  # Prompt the user to enter a choice
                if choice.lower() == 'k':  # If the choice is 'k'
                    break  # Exit the loop and end the program

        except sr.RequestError as e:  # If there is a request error
            print("Could not request results; {0}".format(e))  # Print the error message

        except sr.UnknownValueError:  # If there is an unknown value error
            print("Unknown error occurred")  # Print the error message

        choice = input("Press 'k' to quit or any other key to continue: ")  # Prompt the user to enter a choice
        if choice.lower() == 'k':  # If the choice is 'k'
            break  # Exit the loop and end the program

# Main function to handle user input and execute functions
def main():
    while True:
        print("Select a function to execute:")
        print("1. Response System")
        print("2. Humanoid Motions (Gaits Available: [Welcome, Greetings, and Dance])")
        print("3. Quit")
        choice = input("Enter your choice (1, 2, or 3): ")

        if choice == '1':
            response_system()  # Call the response_system function
        elif choice == '2':
            humanoid_motions()  # Call the humanoid_motions function
        elif choice == '3':
            break  # Exit the loop and end the program
        else:
            print("Invalid choice. Please enter 1, 2, or 3.")

if __name__ == '__main__':
    main()  # Call the main function to start the program
