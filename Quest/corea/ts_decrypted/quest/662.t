CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 662;
	title = 66202;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 66208;
				gtype = 1;
				area = 66201;
				goal = 66204;
				grade = 132203;
				rwd = 100;
				sort = 66205;
				stype = 2;
				taid = 1;
				title = 66202;
			}
			CDboTSActNPCConv
			{
				conv = 66209;
				ctype = 1;
				idx = 4751104;
				taid = 2;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 66214;
			nextlnk = 254;
			rwdtbl = 66201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4191106;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 66208;
			gtype = 1;
			oklnk = 2;
			area = 66201;
			goal = 66204;
			sort = 66205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 66202;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 66207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4751104;
			}
			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSCheckLvl
			{
				maxlvl = 30;
				minlvl = 22;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
	}
}

