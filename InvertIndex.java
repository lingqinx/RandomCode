import java.io.File;
import java.io.IOException;
import java.util.*;
import java.util.StringTokenizer;

import org.apache.commons.io.FileUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class InvertIndex {
	
	public static class InvertIndexMapper extends Mapper<Object, Text, Text, Text>{

	    private Text word = new Text();
	    private Text docId = new Text();
	    public final Log log = LogFactory.getLog(InvertIndexMapper.class);

	    public void map(Object key, Text value, Context context
	                    ) throws IOException, InterruptedException {
	    		String line = value.toString();
	    		StringTokenizer itr = new StringTokenizer(line.split("\t")[1]);
                docId.set(line.split("\t")[0]);
                while (itr.hasMoreTokens()) {
                        word.set(itr.nextToken());
                        context.write(word, docId);
                	}
		
	    }
	}
	
	public static class InvertIndexReducer extends Reducer<Text,Text,Text,Text> {
	    private Text output = new Text();
	    public final Log log = LogFactory.getLog(InvertIndexReducer.class);
	    public void reduce(Text key, Iterable<Text> values, Context context
	                       ) throws IOException, InterruptedException {
	    		HashMap<String,Integer> docIdCount = new HashMap<String,Integer>();
	    		for (Text val : values) {
	    			if(docIdCount.containsKey(val.toString())){
	    				docIdCount.put(val.toString(),docIdCount.get(val.toString())+1);
	    	        }else {
	    	        		docIdCount.put(val.toString(), 1);
	    	        }
	    		}
	      
	    		StringBuilder outputfile = new StringBuilder();
                for(Map.Entry<String, Integer> pair : docIdCount.entrySet())
                	outputfile.append(pair.getKey() + ":" + pair.getValue() + "\t");               
	      
	      output.set(outputfile.toString());
	      context.write(key, output); 
	    }

	}


	public static void main(String []args) throws
	IOException, ClassNotFoundException, InterruptedException{
		if(args.length != 2){
			System.err.println("Usage: InvertIndex <input_path> <output_path>");
			System.exit(-1);
		}
		
		Job job = new Job();
		job.setJarByClass(InvertIndex.class);
		job.setJobName("InvertIndex");
		FileInputFormat.addInputPath(job, new Path(args[0]));
		FileOutputFormat.setOutputPath(job, new Path(args[1]));		
		job.setMapperClass(InvertIndexMapper.class);
		job.setReducerClass(InvertIndexReducer.class);		
		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(Text.class);
		job.waitForCompletion(true);
	}
  
}