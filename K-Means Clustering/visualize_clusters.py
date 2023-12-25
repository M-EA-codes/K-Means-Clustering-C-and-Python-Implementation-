import pandas as pd
import numpy as np
from sklearn.cluster import KMeans

# Load the data into a pandas dataframe
df = pd.read_csv('data.csv')

# Select only the 'Distance' and 'Speed' columns
X = df[['Distance', 'Speed']]

# Create a KMeans model with 2 clusters
kmeans = KMeans(n_clusters=2)

# Fit the data to the model
kmeans.fit(X)

# Get the cluster labels for each data point
labels = kmeans.predict(X)

# Add the cluster labels as a new column in the dataframe
df['Cluster'] = labels

# Print the dataframe with cluster labels
print(df)
