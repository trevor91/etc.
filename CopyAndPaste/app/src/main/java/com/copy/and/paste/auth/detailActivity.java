package com.copy.and.paste.auth;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.copy.and.paste.auth.R;

public class detailActivity extends AppCompatActivity {

    FirebaseDatabase database = FirebaseDatabase.getInstance();
    DatabaseReference myRef = database.getReference("rank");

    private DatabaseReference mDatabase = FirebaseDatabase.getInstance().getReference("rank");
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_detail);

        TextView text = (TextView) findViewById(R.id.detail_textView);
        //Query recentPostsQuery = myRef.child("posts").limitToFirst(100);


    }

}
