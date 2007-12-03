
#ifndef __LOGGER_H__
#define __LOGGER_H__

#define LOG_OUTPUTFILES_HASHTABLE_SIZE	512
#define LOG_MAX_ID_LENGTH				32

typedef struct log_outputfile_s
{
	char					*filename;		// Expanded filename.
	FILE					*file;			// The file pointer to the opened file.
	long					filename_hash;	// A hash of the expanded filename.
	struct log_outputfile_s	*next;			// Pointer to the next outputfile (if there's a collision in the hash table).
} log_outputfile_t; 

typedef enum log_eventlogger_type_s
{
	UNKNOWN,
	LOG_DEATH,
	LOG_MOVE,
	LOG_MATCHSTART,
	LOG_MATCHEND,
	LOG_DEMOSTART,
	LOG_DEMOEND,
	LOG_SPAWN,
	LOG_ITEMPICKUP
} log_eventlogger_type_t;

typedef struct log_outputfile_template_s
{
	char	id[LOG_MAX_ID_LENGTH];
	char	*name;
	//struct log_outputfile_template_s *next;
} log_outputfile_template_t;

typedef struct log_eventlogger_s
{
	int							id;							// The unique ID for the event logger.
	log_eventlogger_type_t		type;						// The type of events this logger logs.
	char 						*output_template_string;	// A string containing the template used when outputting data to the outputfiles.
	log_outputfile_template_t	**outputfile_templates;		// The output file templates associated with this event.
	int							templates_count;			// The number of output file templates.
} log_eventlogger_t;

typedef struct logger_s
{
	log_outputfile_t			output_hashtable[LOG_OUTPUTFILES_HASHTABLE_SIZE];	// Table of opened output files.
	
	log_outputfile_template_t	**output_file_templates;							// Non-expanded file names, such as %playernum%.log
	int							output_file_template_count;							// The number of output file templates.
	
	log_eventlogger_t			**event_loggers;									// Event loggers that outputs the log data to file(s).
	int							event_logger_count;									// The number of event loggers.
} logger_t;

void Log_ClearLogger(logger_t *logger);
qbool Log_ParseOutputTemplates(logger_t *logger, const char *template_file);
void LogVarHashTable_Test(mvd_info_t *mvd);

#endif // __LOGGER_H__
