CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 242;
	title = 24202;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 102;
			elnk = 254;
			nextlnk = 104;
			prelnk = "101;";

			CDboTSActWorldPlayScript
			{
				sid = 242;
				start = 1;
				taid = 1;
				uof = 1;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 1;
			}
		}
		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 102;
			prelnk = "100;";

			CDboTSActTWaitTS
			{
				taid = 2;
				time = 2000;
			}
		}
		CDboTSContGAct
		{
			cid = 104;
			elnk = 255;
			nextlnk = 254;
			prelnk = "102;";

			CDboTSActWorldPlayScript
			{
				sid = 242;
				start = 0;
				taid = 1;
				uof = 0;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 1;
				idx0 = -1;
				cnt0 = 0;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = -1;
				taid = 2;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "102;104;";
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
			stdiag = 24207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 5533401;
			}
			CDboTSCheckLvl
			{
				maxlvl = 15;
				minlvl = 7;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 24214;
			nextlnk = 101;
			rwdtbl = 24201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 3;
				iidx = 468;
			}
			CDboTSClickNPC
			{
				npcidx = 5533401;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 24208;
				gtype = 2;
				area = 24201;
				goal = 24204;
				m0fz = "-3175.000000";
				m0widx = 1;
				sort = 24205;
				stype = 2;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "4376.000000";
				m0ttip = 24215;
				rwd = 100;
				taid = 1;
				title = 24202;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 1;
				idx0 = 468;
				cnt0 = 3;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
			CDboTSActNPCConv
			{
				conv = 24209;
				ctype = 1;
				idx = 5533401;
				taid = 2;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 24208;
			gtype = 2;
			oklnk = 2;
			area = 24201;
			goal = 24204;
			sort = 24205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 24202;
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 0;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
		CDboTSContGCond
		{
			cid = 1;
			prelnk = "0;";
			nolnk = 254;
			rm = 0;
			yeslnk = 2;

			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 1;
				iidx = 468;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;2;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 254;
			prelnk = "1;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 468;
				taid = 1;
				type = 1;
			}
		}
	}
}

