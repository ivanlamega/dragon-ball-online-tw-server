CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 203;
	title = 20302;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGCond
		{
			cid = 4;
			prelnk = "100;2;";
			nolnk = 255;
			rm = 1;
			yeslnk = 3;

			CDboTSClickNPC
			{
				npcidx = 4211101;
			}
		}
		CDboTSContUnifiedNarration
		{
			cancellnk = 100;
			cid = 3;
			idx = 2033;
			lilnk = 255;
			oklnk = 100;
			prelnk = "4;";
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 4;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 20308;
				gtype = 1;
				area = 20301;
				goal = 20304;
				grade = 132203;
				rwd = 100;
				sort = 20305;
				stype = 2;
				taid = 1;
				title = 20302;
			}
			CDboTSActNPCConv
			{
				conv = 20309;
				ctype = 1;
				idx = 4511205;
				taid = 2;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 20308;
			gtype = 1;
			oklnk = 2;
			area = 20301;
			goal = 20304;
			sort = 20305;
			prelnk = "0;";
			ds = 0;
			grade = 132203;
			rwd = 100;
			title = 20302;
		}
		CDboTSContReward
		{
			canclnk = 4;
			cid = 100;
			desc = 20314;
			nextlnk = 254;
			rwdtbl = 20301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;3;";
			usetbl = 1;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 20307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckLvl
			{
				maxlvl = 9;
				minlvl = 1;
			}
			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 4511205;
			}
			CDboTSCheckClrQst
			{
				or = "202;";
			}
		}
	}
}

