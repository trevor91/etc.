package com.copy.and.paste.auth;

import android.content.DialogInterface;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.copy.and.paste.auth.R;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.Calendar;

public class threebythree extends AppCompatActivity implements View.OnClickListener, method{

    Animation anim;
    Button btn_start;
    Button btn1;
    Button btn2;
    Button btn3;
    Button btn4;
    Button btn5;
    Button btn6;
    Button btn7;
    Button btn8;
    Button btn9;
    TextView textView;

    int arrLength = 5; //length of answer
    ArrayList<Integer> list = new ArrayList<Integer>(); //answer value.
    int cnt =0;//animation count
    int index=0; //check the input
    int opportunity=2;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_threebythree);
        btn_start = (Button)findViewById(R.id.three_btn_start);
        btn1 = (Button)findViewById(R.id.three_btn1);
        btn2 = (Button)findViewById(R.id.three_btn2);
        btn3 = (Button)findViewById(R.id.three_btn3);
        btn4 = (Button)findViewById(R.id.three_btn4);
        btn5 = (Button)findViewById(R.id.three_btn5);
        btn6 = (Button)findViewById(R.id.three_btn6);
        btn7 = (Button)findViewById(R.id.three_btn7);
        btn8 = (Button)findViewById(R.id.three_btn8);
        btn9 = (Button)findViewById(R.id.three_btn9);

        textView = (TextView)findViewById(R.id.three_TextView);

        btn_start.setOnClickListener(this);
        btn1.setOnClickListener(this);
        btn2.setOnClickListener(this);
        btn3.setOnClickListener(this);
        btn4.setOnClickListener(this);
        btn5.setOnClickListener(this);
        btn6.setOnClickListener(this);
        btn7.setOnClickListener(this);
        btn8.setOnClickListener(this);
        btn9.setOnClickListener(this);
        textView.setText("index length: "+arrLength+", current index: "+index+", opportunity: "+opportunity);
        createAn();
    }
    @Override
    public void onClick(View v) {
        switch(v.getId()){
            case R.id.three_btn_start:
                index=0;
                textView.setText("index length: "+arrLength+", current index: "+index+", opportunity: "+opportunity);
                //make answer
                if(list.isEmpty()){ //Game start
                    for(int i=0;i<arrLength;i++) {
                        list.add(getRandomMath(9,1));
                    }
                }
                btn_start.startAnimation(anim);
                btn_start.setText("waiting ");
                break;
            case R.id.three_btn1:   btnFunc(1); break;
            case R.id.three_btn2:   btnFunc(2); break;
            case R.id.three_btn3:   btnFunc(3); break;
            case R.id.three_btn4:   btnFunc(4); break;
            case R.id.three_btn5:   btnFunc(5); break;
            case R.id.three_btn6:   btnFunc(6); break;
            case R.id.three_btn7:   btnFunc(7); break;
            case R.id.three_btn8:   btnFunc(8); break;
            case R.id.three_btn9:   btnFunc(9); break;
        }
    }
    @Override
    public int getRandomMath(int max, int offset) {
        int nResult = (int)(Math.random() * max) + offset;
        return nResult;
    }
    @Override
    public void createAn() {
        anim= AnimationUtils.loadAnimation(this,R.anim.alpha);
        anim.setAnimationListener(new Animation.AnimationListener() {
            @Override
            public void onAnimationStart(Animation animation) {}
            @Override
            public void onAnimationEnd(Animation animation) {
                //COPY area
                if(cnt<arrLength){
                    switch(list.get(cnt)){
                        case 1: btn1.startAnimation(anim);  break;
                        case 2: btn2.startAnimation(anim);  break;
                        case 3: btn3.startAnimation(anim);  break;
                        case 4: btn4.startAnimation(anim);  break;
                        case 5: btn5.startAnimation(anim);  break;
                        case 6: btn6.startAnimation(anim);  break;
                        case 7: btn7.startAnimation(anim);  break;
                        case 8: btn8.startAnimation(anim);  break;
                        case 9: btn9.startAnimation(anim);  break;
                    }
                    ++cnt;
                }
                else if(cnt==arrLength){
                    btn_start.setText("RESTART");
                    cnt=0;
                }
            }
            @Override
            public void onAnimationRepeat(Animation animation) {}
        });
    }

    @Override
    public boolean inputCheck(ArrayList<Integer> list, int input, int index) {
        if(list.get(index) == input){return true;}
        return false;
    }

    @Override
    public void btnFunc(int btnValue) {
        if(list.isEmpty()){
            Toast.makeText(this,"Push the start button",Toast.LENGTH_SHORT).show();return;}
        //
        if(inputCheck(list,btnValue,index)){ //정답이면
            index++;
            if(index==arrLength){ //done.
                Toast.makeText(this,"Correct answer :)",Toast.LENGTH_SHORT).show();
                btn_start.setText("Next stage");
                arrLength++;
                index=0;
                list.clear();
                opportunity++;
            }
            else{ //ing...
                //Toast.makeText(this,"nice.",Toast.LENGTH_SHORT).show();
            }
            textView.setText("index length: "+arrLength+", current index: "+index+", opportunity: "+opportunity);
        }
        else{ //틀린 답이면
            if(opportunity != 0){ //기회가 남았으면
                --opportunity;
                Toast.makeText(this, "Wrong answer :( opportunity: "+opportunity,Toast.LENGTH_SHORT).show();
            }
            else{ //기회가 없으면
                AlertDialog.Builder builder = new AlertDialog.Builder(this);
                builder.setTitle("End.");
                builder.setMessage("your record: "+arrLength);
                builder.setNeutralButton("back", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        //JSON
                        JSONObject json = new JSONObject();
                        try {
                            json.put("id",getIntent().getStringExtra("id"));
                            json.put("position","3*3");
                            json.put("length",arrLength);
                        } catch (JSONException e1) {
                            e1.printStackTrace();
                        }
                        JSONArray data = new JSONArray();
                        data.put(json);

                        Calendar calendar = Calendar.getInstance();
                        String time = calendar.getTime().toString();

                        //Data trans.
                        FirebaseDatabase database = FirebaseDatabase.getInstance();
                        DatabaseReference myRef = database.getReference("rank");
                        myRef.child(time).setValue(data.toString());

                        finish();
                    }
                });
                builder.show();
            }
            textView.setText("index length: "+arrLength+", current index: "+index+", opportunity: "+opportunity);
        }
    }
}
