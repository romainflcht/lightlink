from flask import Flask, render_template
from flask_restful import Api, Resource, reqparse, abort
import glob
import time
import json
import os


ACCOUNTS_DIR = "accounts"

app = Flask(__name__)
api = Api(app)


drawing_post_args = reqparse.RequestParser()
drawing_post_args.add_argument("timestamp", type=int, location="json")
drawing_post_args.add_argument("width", type=int, location="json")
drawing_post_args.add_argument("height", type=int, location="json")
drawing_post_args.add_argument("pixel_map", type=list, location="json")


class Drawings(Resource):
    def get(self, device_id, fetching_only_ts):
        account_path = os.path.join(ACCOUNTS_DIR, device_id)

        # Check if the device id exist or not. 
        if (not os.path.isdir(account_path)):
            abort(404, message=f"Device id ({device_id}) does not exist...")
        
        # Fetch all drawings linked to the account. 
        drawings = glob.glob(os.path.join(account_path, '*.json'))

        # Check if there is at least 1 drawing linked.
        if (drawings == []):
            abort(404, message=f"No drawings linked to account id ({device_id})...")

        # Get the most recent drawing.
        latest_drawing = max(drawings)

        if fetching_only_ts: 
            timestamp = os.path.splitext(os.path.basename(latest_drawing))[0]
            return ({"timestamp": int(timestamp)}, 200)

        # Send the json file. 
        with open(latest_drawing, 'r') as drawing_json: 
            data = json.load(drawing_json)
        
        return (data, 200)


    def post(self, device_id, fetching_only_ts): 
        # # Get POST arguments. 
        args = drawing_post_args.parse_args()
        
        receiver_account_path = os.path.join(ACCOUNTS_DIR, device_id)

        # Check if the receiver device id exist or not. 
        if (not os.path.isdir(receiver_account_path)):
            abort(404, message=f"Device id ({device_id}) does not exist...")

        # Get the timestamp of the payload.
        timestamp = args.get("timestamp", None)
        if (timestamp is None):
            # If the timestamp is empty, add one. 
            timestamp = time.time()

        with open(os.path.join(receiver_account_path, f"{timestamp}.json"), "w") as drawing_json:
            try:
                # Save json data to a file. 
                json.dump(args, drawing_json)
                drawings = glob.glob(os.path.join(receiver_account_path, '*.json'))

                if (len(drawings) > 10):
                    oldest_drawing = min(drawings)
                    os.remove(oldest_drawing)
            
            except TypeError:
                abort(415, message="Error when parsing json data...")
        
        return ({"message": "OK"}, 201)
    


class History(Resource):
    def get(self, device_id):
        account_path = os.path.join(ACCOUNTS_DIR, device_id)

        # Check if the device id exist or not. 
        if (not os.path.isdir(account_path)):
            abort(404, message=f"Device id ({device_id}) does not exist...")
        
        # Fetch all drawings linked to the account. 
        drawings = glob.glob(os.path.join(account_path, '*.json'))

        # Check if there is at least 1 drawing linked.
        if (drawings == []):
            abort(404, message=f"No drawings linked to account id ({device_id})...")

        json_history = {"history": []}


        # Send the json file. 
        for drawing in drawings: 
            with open(drawing, 'r') as drawing_json: 
                json_history["history"].append(json.load(drawing_json))
        
        return (json_history, 200)



api.add_resource(Drawings, "/img/<string:device_id>/<int:fetching_only_ts>")
api.add_resource(History, "/history/<string:device_id>")



@app.route('/')
def home():
    return render_template("index.html")

@app.route('/settings')
def settings():
    return render_template("settings.html")

@app.route('/exhibition')
def exhibition():
    return render_template("exhibition.html")



if __name__ == "__main__":
    app.run(host='0.0.0.0', port='5000')
    