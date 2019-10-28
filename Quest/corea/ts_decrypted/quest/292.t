CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 292;
	title = 29202;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 16;
			elnk = 255;
			nextlnk = 100;
			prelnk = "15;";

			CDboTSActWorldPlayScript
			{
				sid = 292;
				start = 0;
				taid = 1;
				uof = 0;
			}
		}
		CDboTSContGAct
		{
			cid = 4;
			elnk = 252;
			nextlnk = 11;
			prelnk = "2;";

			CDboTSActWorldPlayScript
			{
				sid = 292;
				start = 1;
				taid = 1;
				uof = 1;
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
				taeid = 3;
				taid = 3;
				tceid = 11;
			}
			CDboTSActETimerE
			{
				taeid = 1;
				taid = 1;
				tceid = 11;
			}
		}
		CDboTSContGCond
		{
			cid = 14;
			prelnk = "11;";
			nolnk = 255;
			rm = 0;
			yeslnk = 15;

			CDboTSRcvSvrEvt
			{
				id = 5;
			}
		}
		CDboTSContGAct
		{
			cid = 11;
			elnk = 252;
			nextlnk = 14;
			prelnk = "4;";

			CDboTSActETimerS
			{
				sort = 1;
				taid = 1;
				tgid = 11;
				time = 2000;
			}
			CDboTSActETimerS
			{
				sort = 1;
				taid = 2;
				tgid = 12;
				time = 2000;
			}
			CDboTSActETimerS
			{
				sort = 0;
				taid = 3;
				tgid = 1;
				time = 600000;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "4;11;2;";
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 29207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 3;
			}
			CDboTSClickNPC
			{
				npcidx = 4751201;
			}
			CDboTSCheckLvl
			{
				maxlvl = 22;
				minlvl = 14;
			}
			CDboTSCheckClrQst
			{
				and = "281;";
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 29208;
			gtype = 1;
			oklnk = 2;
			area = 29201;
			goal = 29204;
			sort = 29205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 29202;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 4;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 29209;
				ctype = 1;
				idx = 4751201;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 29208;
				gtype = 1;
				area = 29201;
				goal = 29204;
				m0fz = "-2386.510010";
				m0widx = 1;
				sort = 29205;
				stype = 1;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "4801.569824";
				m0ttip = 29215;
				rwd = 100;
				taid = 1;
				title = 29202;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 29214;
			nextlnk = 254;
			rwdtbl = 29201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "16;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 6312101;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 12;

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
			stdiag = 29207;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckNPCDead
			{
				idxlist = "4451101;";
			}
		}
	}
	CNtlTSGroup
	{
		gid = 1;

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
		CDboTSContEnd
		{
			cid = 2;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 29207;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
	CNtlTSGroup
	{
		gid = 11;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 29207;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckDistWithNPC
			{
				dist = "30.000000";
				idxlist = "4451101;";
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
}

