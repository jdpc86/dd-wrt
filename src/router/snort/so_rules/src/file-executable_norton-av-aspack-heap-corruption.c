/*
 * Vuln Title: XXXX
 *
 * Copyright (C) 2005-2010 Sourcefire, Inc. All Rights Reserved
 *
 * Written by XXXX, Sourcefire VRT <XXXX@sourcefire.com>
 *
 * Auto-generated by XXXX
 *
 * This file may contain proprietary rules that were created, tested and
 * certified by Sourcefire, Inc. (the "VRT Certified Rules") as well as
 * rules that were created by Sourcefire and other third parties and
 * distributed under the GNU General Public License (the "GPL Rules").  The
 * VRT Certified Rules contained in this file are the property of
 * Sourcefire, Inc. Copyright 2005 Sourcefire, Inc. All Rights Reserved.
 * The GPL Rules created by Sourcefire, Inc. are the property of
 * Sourcefire, Inc. Copyright 2002-2005 Sourcefire, Inc. All Rights
 * Reserved.  All other GPL Rules are owned and copyrighted by their
 * respective owners (please see www.snort.org/contributors for a list of
 * owners and their respective copyrights).  In order to determine what
 * rules are VRT Certified Rules or GPL Rules, please refer to the VRT
 * Certified Rules License Agreement.
 */

#include "sf_snort_plugin_api.h"
#include "sf_snort_packet.h"

#include "so-util.h"

//#define DEBUG
#ifdef DEBUG
#define DEBUG_SO(code) code
#else
#define DEBUG_SO(code)
#endif

/* declare detection functions */
int rule39379eval(void *p);

/* declare rule data structures */
/* flow:established, to_client; */
static FlowFlags rule39379flow0 = 
{
   FLOW_ESTABLISHED|FLOW_TO_CLIENT
};

static RuleOption rule39379option0 =
{
   OPTION_TYPE_FLOWFLAGS,
   {
      &rule39379flow0
   }
};

/* flowbits:isset "file.exe"; */
static FlowBitsInfo rule39379flowbits1 =
{
   "file.exe",
   FLOWBIT_ISSET,
   0,
};

static RuleOption rule39379option1 =
{
   OPTION_TYPE_FLOWBIT,
   {
      &rule39379flowbits1
   }
};

// file_data;
static CursorInfo rule39379file_data2 =
{
   0, /* offset */
   CONTENT_BUF_NORMALIZED /* flags */
};

static RuleOption rule39379option2 =
{
#ifndef MISSINGFILEDATA
   OPTION_TYPE_FILE_DATA,
#else
   OPTION_TYPE_SET_CURSOR,
#endif
   {
      &rule39379file_data2
   }
};

/* byte_jump:size 4, offset 60, endian little, from_beginning; */
static ByteData rule39379byte_jump3 = 
{
   4, /* size */
   0, /* operator, byte_jump doesn't use operator! */
   0, /* value, byte_jump doesn't use value! */
   60, /* offset */
   #ifdef MISSING_BYTE_JUMP_FIX
   1, /* XXX BUG 76359 */ /* multiplier */
#else
   0, /* multiplier */
#endif
   BYTE_LITTLE_ENDIAN|JUMP_FROM_BEGINNING|CONTENT_BUF_NORMALIZED|EXTRACT_AS_BYTE /* flags */
};

static RuleOption rule39379option3 = 
{
   OPTION_TYPE_BYTE_JUMP,
   {
      &rule39379byte_jump3
   }
};

// content:"PE|00 00|", depth 4, relative, fast_pattern; 
static ContentInfo rule39379content4 = 
{
   (u_int8_t *) "PE|00 00|", /* pattern (now in snort content format) */
   4, /* depth */
   0, /* offset */
   CONTENT_RELATIVE|CONTENT_FAST_PATTERN|CONTENT_BUF_NORMALIZED, /* flags */
   NULL, /* holder for boyer/moore PTR */
   NULL, /* more holder info - byteform */
   0, /* byteform length */
   0 /* increment length*/
};

static RuleOption rule39379option4 = 
{
   OPTION_TYPE_CONTENT,
   {
      &rule39379content4
   }
};

/* references for sid 39379 */
/* reference: cve "2016-1111"; */
static RuleReference rule39379ref1 = 
{
   "cve", /* type */
   "2016-2208" /* value */
};

/* reference: url "googleprojectzero.blogspot.com/2016/06/how-to-compromise-enterprise-endpoint.html"; */
static RuleReference rule39379ref2 =
{
   "url", /* type */
   "googleprojectzero.blogspot.com/2016/06/how-to-compromise-enterprise-endpoint.html" /* value */
};

static RuleReference *rule39379refs[] =
{
   &rule39379ref1,
   &rule39379ref2,
   NULL
};

/* metadata for sid 39379 */
/* metadata:service ftp-data, service http, service imap, service pop3, policy balanced-ips drop, policy security-ips drop; */
static RuleMetaData rule39379service1 = 
{
   "service ftp-data"
};

static RuleMetaData rule39379service2 = 
{
   "service http"
};

static RuleMetaData rule39379service3 = 
{
   "service imap"
};

static RuleMetaData rule39379service4 = 
{
   "service pop3"
};

static RuleMetaData rule39379policy1 = 
{
   "policy balanced-ips drop"
};

static RuleMetaData rule39379policy2 = 
{
   "policy security-ips drop"
};

static RuleMetaData rule39379policy3 =
{
   "policy max-detect-ips drop"
};

static RuleMetaData *rule39379metadata[] =
{
   &rule39379service1,
   &rule39379service2,
   &rule39379service3,
   &rule39379service4,
   &rule39379policy1,
   &rule39379policy2,
   &rule39379policy3,
   NULL
};

RuleOption *rule39379options[] =
{
   &rule39379option0,
   &rule39379option1,
   &rule39379option2,
   &rule39379option3,
   &rule39379option4,
   NULL
};

Rule rule39379 = {
   /* rule header, akin to => tcp any any -> any any */
   {
      IPPROTO_TCP, /* proto */
      "$EXTERNAL_NET", /* SRCIP     */
      "$FILE_DATA_PORTS", /* SRCPORT   */
      0, /* DIRECTION */
      "$HOME_NET", /* DSTIP     */
      "any", /* DSTPORT   */
   },
   /* metadata */
   { 
      3,  /* genid */
      39379, /* sigid */
      2, /* revision */
      "attempted-admin", /* classification */
      0,  /* hardcoded priority */
      "FILE-EXECUTABLE Norton Antivirus ASPack heap corruption attempt",     /* message */
      rule39379refs, /* ptr to references */
      rule39379metadata /* ptr to metadata */
   },
   rule39379options, /* ptr to rule options */
   &rule39379eval, /* use custom detection function */
   0 /* am I initialized yet? */
};


/* detection functions */
int rule39379eval(void *p) {
   const u_int8_t *cursor_normal = 0;
   const u_int8_t *beg_of_payload, *end_of_payload;
   SFSnortPacket *sp = (SFSnortPacket *) p;

   uint16_t numOfSections, sizeOfOptional = 0;
   uint32_t sizeofImage = 0;

   int i;

   DEBUG_SO(fprintf(stderr, "ENTER\n");)

   if(sp == NULL)
      return RULE_NOMATCH;

   if(sp->payload == NULL)
      return RULE_NOMATCH;
   
   // flow:established, to_client;
   if(checkFlow(p, rule39379options[0]->option_u.flowFlags) <= 0)
      return RULE_NOMATCH;
   
   // flowbits:isset "file.exe";
   if(processFlowbits(p, rule39379options[1]->option_u.flowBit) <= 0)
      return RULE_NOMATCH;
   
   // file_data;
   #ifndef MISSINGFILEDATA
   if(fileData(p, rule39379options[2]->option_u.cursor, &cursor_normal) <= 0)
      return RULE_NOMATCH;
   #else
   if(setCursor(p, rule39379options[2]->option_u.cursor, &cursor_normal) <= 0)
      return RULE_NOMATCH;
   #endif
   
   // Pull e_lfanew value from DOS header and jump to start of PE header.
   // byte_jump:size 4, offset 60, endian little, from_beginning;
   if(byteJump(p, rule39379options[3]->option_u.byte, &cursor_normal) <= 0)
      return RULE_NOMATCH;
   
   // content:"PE|00 00|", depth 4, relative, fast_pattern;
   if(contentMatch(p, rule39379options[4]->option_u.content, &cursor_normal) <= 0)
      return RULE_NOMATCH;
   
   // Set end of payload for out of bounds checking.
   if(getBuffer(sp, CONTENT_BUF_NORMALIZED, &beg_of_payload, &end_of_payload) <= 0)
      return RULE_NOMATCH;

   // Check for size of IMAGE_FILE_HEADER plus some other reads we know we'll be doing
   if(cursor_normal + 100 > end_of_payload)
      return RULE_NOMATCH;

   // Find number of Sections
   numOfSections = read_little_16(cursor_normal + 2);
   DEBUG_SO(printf("Number of Sections: 0x%04x\n", numOfSections));

   if(numOfSections == 0)
      return RULE_NOMATCH;

   // Limit number of loops later
   if(numOfSections > 20)
      numOfSections = 20;

   // Find size of optional header
   sizeOfOptional = read_little_16(cursor_normal + 16);
   DEBUG_SO(printf("Size of Optional Header: 0x%04x\n", sizeOfOptional));
   if(sizeOfOptional < 60) // minimum needed to read 4-byte sizeofImage at offset 56
      return RULE_NOMATCH;
   if(sizeOfOptional > 3000) // Detection of "funny stuff" and protection from integer/pointer overflow below 
      return RULE_NOMATCH;

   // Move cursor to beginning of optional header then verify payload length (section headers are 40 bytes)
   cursor_normal += 20;

   // Addition is max of 3800, so not checking for overflow
   if(cursor_normal + sizeOfOptional + (40 * numOfSections) > end_of_payload) 
      return RULE_NOMATCH;

   // Pull sizeofImage from optional header
   sizeofImage = read_little_32(cursor_normal + 56);
   DEBUG_SO(printf("Size of Image:    0x%08x\n", sizeofImage));

   // Jump to end of optional header for section table
   cursor_normal += sizeOfOptional;

   // Loop through all Section tables (max limited to 20 above)
   // We check for data availability above
   for(i = 0; i < numOfSections; i++)
   {
      /*
	This check is so that we avoid the ".rsrc" section when performing the final check against the size of image.
	The reason for this is the ".rsrc" section can contain some really large sizes that result in false positives.
	Detection is lost for that specific section, however the alternative would be not releasing coverage.
      */
      if(read_little_64(cursor_normal) != 0x637273722e)
      {
	      // Pull raw size at offset 16 in IMAGE_SECTION_HEADER structure
	      DEBUG_SO(printf("Size of Raw Data: 0x%08x\n", read_little_32(cursor_normal + 16)));
	      // Check if the Size of Raw Image is greater than Size Of Image value. If TRUE, alert.
	      if((read_little_32(cursor_normal + 16)) > sizeofImage)
		 return RULE_MATCH;
      }

      // If we did not alert, increment cursor to next section header
      cursor_normal += 40;
   }

   // No match found.

   return RULE_NOMATCH;
}

/*
Rule *rules[] = {
    &rule39379,
    NULL
};
*/
