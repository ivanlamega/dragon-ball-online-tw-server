CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1371;
	title = 137102;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGCond
		{
			cid = 5;
			prelnk = "100;";
			nolnk = 255;
			rm = 1;
			yeslnk = 100;

			CDboTSClickNPC
			{
				npcidx = 1654103;
			}
		}
		CDboTSContGAct
		{
			cid = 4;
			elnk = 255;
			nextlnk = 100;
			prelnk = "3;";

			CDboTSActETimerE
			{
				taeid = 4;
				taid = 3;
				tceid = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 2;
				idx0 = -1;
				cnt0 = 0;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = -1;
				taid = 1;
				esctype = 0;
				idx2 = -1;
			}
			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 1033;
				taid = 2;
				type = 1;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContReward
		{
			canclnk = 5;
			cid = 100;
			desc = 137114;
			nextlnk = 254;
			rwdtbl = 137101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "5;4;";
			usetbl = 1;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 137107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckLvl
			{
				maxlvl = 54;
				minlvl = 46;
			}
			CDboTSClickNPC
			{
				npcidx = 4372101;
			}
			CDboTSCheckClrQst
			{
				and = "1370;";
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 137108;
			gtype = 1;
			oklnk = 2;
			area = 137101;
			goal = 137104;
			sort = 137105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 137102;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 4;

			CDboTSCheckQItem
			{
				ct = 0;
				icnt = 1;
				iidx = 1033;
			}
			CDboTSClickNPC
			{
				npcidx = 1654103;
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
				cont = 137108;
				gtype = 1;
				area = 137101;
				goal = 137104;
				grade = 132203;
				rwd = 100;
				sort = 137105;
				stype = 1;
				taid = 1;
				title = 137102;
			}
			CDboTSActNPCConv
			{
				conv = 137109;
				ctype = 1;
				idx = 4372101;
				taid = 2;
			}
			CDboTSActETimerS
			{
				sort = 0;
				taid = 4;
				tgid = 1;
				time = 900000;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cd0 = 92029;
				cnt1 = 0;
				eitype = 2;
				idx0 = 1033;
				cnt0 = 1;
				ectype = 0;
				esctype = 0;
				idx2 = -1;
				cnt2 = 0;
				etype = 0;
				idx1 = -1;
				taid = 3;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 1033;
				taid = 1;
				type = 1;
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
			stdiag = 137107;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
	CNtlTSGroup
	{
		gid = 1;

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
			stdiag = 0;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
}

