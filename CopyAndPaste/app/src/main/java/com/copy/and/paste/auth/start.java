package com.copy.and.paste.auth;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import com.copy.and.paste.auth.R;

public class start extends AppCompatActivity implements View.OnClickListener{

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_nbyn);

        Button btn1 = (Button)findViewById(R.id.button2by2);
        Button btn2 = (Button)findViewById(R.id.button3by3);
        Button btn3 = (Button)findViewById(R.id.button4by4);
        Button btn4 = (Button)findViewById(R.id.detail_btn);
        btn1.setOnClickListener(this);
        btn2.setOnClickListener(this);
        btn3.setOnClickListener(this);
        btn4.setOnClickListener(this);
    }
    @Override
    public void onClick(View view) {
        String name = getIntent().getStringExtra("id");
        switch(view.getId())
        {
            case R.id.button2by2:
                Intent intent1 = new Intent(this, twobytwo.class);
                intent1.putExtra("id",name);
                startActivity(intent1);
                break;
            case R.id.button3by3:
                Intent intent2 = new Intent(this, threebythree.class);
                intent2.putExtra("id",name);
                startActivity(intent2);
                break;
            case R.id.button4by4:
                Intent intent3 = new Intent(this, fourbyfour.class);
                intent3.putExtra("id",name);
                startActivity(intent3);
                break;
            case R.id.detail_btn:
                Intent intent4 = new Intent(this, detailActivity.class);
                intent4.putExtra("id",name);
                startActivity(intent4);
                break;
        }
    }
}
