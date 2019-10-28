CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 161;
	title = 16102;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 16108;
				gtype = 4;
				area = 16101;
				goal = 16104;
				m0fz = "-1104.050049";
				m0widx = 2;
				sort = 16105;
				stype = 2;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "920.159973";
				m0ttip = 16115;
				rwd = 100;
				taid = 1;
				title = 16102;
			}
			CDboTSActNPCConv
			{
				conv = 16109;
				ctype = 1;
				idx = 5591105;
				taid = 2;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 16114;
			nextlnk = 254;
			rwdtbl = 16101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "17;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 2801106;
			}
		}
		CDboTSContGCond
		{
			cid = 14;
			prelnk = "13;";
			nolnk = 255;
			rm = 0;
			yeslnk = 15;

			CDboTSRcvSvrEvt
			{
				id = 6;
			}
		}
		CDboTSContGAct
		{
			cid = 15;
			elnk = 255;
			nextlnk = 16;
			prelnk = "14;";

			CDboTSActETimerE
			{
				taeid = 2;
				taid = 2;
				tceid = 11;
			}
			CDboTSActETimerE
			{
				taeid = 4;
				taid = 4;
				tceid = 11;
			}
			CDboTSActETimerE
			{
				taeid = 3;
				taid = 3;
				tceid = 11;
			}
		}
		CDboTSContGAct
		{
			cid = 4;
			elnk = 255;
			nextlnk = 5;
			prelnk = "3;";

			CDboTSActNPCConv
			{
				conv = 16120;
				ctype = 1;
				idx = 7611101;
				taid = 1;
			}
		}
		CDboTSContGAct
		{
			cid = 3;
			elnk = 255;
			nextlnk = 4;
			prelnk = "2;";

			CDboTSActTWaitTS
			{
				taid = 1;
				time = 2000;
			}
		}
		CDboTSContGAct
		{
			cid = 5;
			elnk = 255;
			nextlnk = 11;
			prelnk = "4;";

			CDboTSActTWaitTS
			{
				taid = 1;
				time = 10000;
			}
		}
		CDboTSContGAct
		{
			cid = 12;
			elnk = 255;
			nextlnk = 13;
			prelnk = "11;";

			CDboTSActTWaitTS
			{
				taid = 1;
				time = 10000;
			}
		}
		CDboTSContGAct
		{
			cid = 13;
			elnk = 255;
			nextlnk = 14;
			prelnk = "12;";

			CDboTSActNPCConv
			{
				conv = 16121;
				ctype = 1;
				idx = 5591105;
				taid = 1;
			}
		}
		CDboTSContGAct
		{
			cid = 17;
			elnk = 255;
			nextlnk = 100;
			prelnk = "16;";

			CDboTSActNPCConv
			{
				conv = 16122;
				ctype = 1;
				idx = 5591105;
				taid = 1;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;11;";
		}
		CDboTSContGAct
		{
			cid = 11;
			elnk = 252;
			nextlnk = 12;
			prelnk = "5;";

			CDboTSActETimerS
			{
				sort = 1;
				taid = 2;
				tgid = 11;
				time = 2000;
			}
			CDboTSActETimerS
			{
				sort = 1;
				taid = 3;
				tgid = 12;
				time = 2000;
			}
			CDboTSActETimerS
			{
				sort = 0;
				taid = 4;
				tgid = 1;
				time = 600000;
			}
			CDboTSActEscort
			{
				start = 1;
				tblidx = 5591105;
				tsshare = 1;
				etype = 1;
				taid = 1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 16108;
			gtype = 4;
			oklnk = 2;
			area = 16101;
			goal = 16104;
			sort = 16105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 16102;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 16107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5591105;
			}
			CDboTSCheckLvl
			{
				maxlvl = 27;
				minlvl = 19;
			}
			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "1;252;0;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 16;
			elnk = 255;
			nextlnk = 17;
			prelnk = "15;";

			CDboTSActEscort
			{
				start = 0;
				tblidx = 5591105;
				tsshare = 1;
				etype = 1;
				taid = 1;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 11;

		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActTSState
			{
				state = 2;
				taid = 1;
				type = 0;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 16107;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckDistWithNPC
			{
				dist = "30.000000";
				idxlist = "5591105;";
			}
		}
	}
	CNtlTSGroup
	{
		gid = 12;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 16107;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckNPCDead
			{
				idxlist = "5591105;";
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActTSState
			{
				state = 2;
				taid = 1;
				type = 0;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 1;

		CDboTSContEnd
		{
			cid = 2;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 2;
			prelnk = "0;";

			CDboTSActTSState
			{
				state = 2;
				taid = 1;
				type = 0;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 16107;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
}

